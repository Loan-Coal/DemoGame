#include "NpcEngineWsClient.h"
#include "NpcEngineClient.h"
#include "NpcEngineJsonUtils.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// BUILT BUT NOT WIRED IN SLICE-1.
// Wire slice-1 gameplay to UNpcEngineRestClient instead.

FNpcEngineWebSocketClient::~FNpcEngineWebSocketClient()
{
    Disconnect();
}

void FNpcEngineWebSocketClient::Connect(const FString& WsUrl, const FString& BearerToken)
{
    if (WebSocket.IsValid() && WebSocket->IsConnected())
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("WsClient: already connected, ignoring Connect()."));
        return;
    }

    // Auth via the WS handshake header — bad/missing key causes server close 1008.
    const TMap<FString, FString> Headers = {
        { TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *BearerToken) }
    };

    WebSocket = FWebSocketsModule::Get().CreateWebSocket(WsUrl, TEXT(""), Headers);

    WebSocket->OnConnected().AddRaw(this, &FNpcEngineWebSocketClient::OnConnected);
    WebSocket->OnConnectionError().AddRaw(this, &FNpcEngineWebSocketClient::OnConnectionError);
    WebSocket->OnClosed().AddRaw(this, &FNpcEngineWebSocketClient::OnClosed);
    WebSocket->OnMessage().AddRaw(this, &FNpcEngineWebSocketClient::OnMessage);

    WebSocket->Connect();
    UE_LOG(LogNpcEngine, Log, TEXT("WsClient: connecting to %s"), *WsUrl);
}

void FNpcEngineWebSocketClient::SendDialogueRequest(const FNpcDialogueRequest& Request)
{
    if (!IsConnected())
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("WsClient: SendDialogueRequest called but not connected."));
        return;
    }
    AccumulatedTokens.Empty();
    const FString Body = FNpcEngineJsonUtils::SerialiseDialogueRequest(Request);
    WebSocket->Send(Body);
}

void FNpcEngineWebSocketClient::Disconnect()
{
    if (WebSocket.IsValid())
    {
        WebSocket->Close();
        WebSocket.Reset();
    }
    AccumulatedTokens.Empty();
}

bool FNpcEngineWebSocketClient::IsConnected() const
{
    return WebSocket.IsValid() && WebSocket->IsConnected();
}

// ── Private handlers ─────────────────────────────────────────────────────────

void FNpcEngineWebSocketClient::OnConnected()
{
    UE_LOG(LogNpcEngine, Log, TEXT("WsClient: connected."));
}

void FNpcEngineWebSocketClient::OnConnectionError(const FString& Error)
{
    UE_LOG(LogNpcEngine, Warning, TEXT("WsClient: connection error: %s"), *Error);
    if (OnDialogueError)
    {
        OnDialogueError(Error);
    }
}

void FNpcEngineWebSocketClient::OnClosed(int32 StatusCode, const FString& Reason, bool /*bWasClean*/)
{
    UE_LOG(LogNpcEngine, Log, TEXT("WsClient: closed (code %d, reason: %s)."), StatusCode, *Reason);
    // Code 1008 = auth failure; code 1011 = server error.
    if (StatusCode == 1008 || StatusCode == 1011)
    {
        if (OnDialogueError)
        {
            OnDialogueError(FString::Printf(TEXT("WS closed %d: %s"), StatusCode, *Reason));
        }
    }
}

void FNpcEngineWebSocketClient::OnMessage(const FString& Message)
{
    TSharedPtr<FJsonObject> Msg;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
    if (!FJsonSerializer::Deserialize(Reader, Msg) || !Msg.IsValid())
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("WsClient: malformed message: %s"), *Message);
        return;
    }

    const FString Type = Msg->GetStringField(TEXT("type"));

    if (Type == TEXT("token"))
    {
        const FString Chunk = Msg->GetStringField(TEXT("data"));
        AccumulatedTokens += Chunk;
        if (OnDialogueChunk)
        {
            OnDialogueChunk(Chunk);
        }
    }
    else if (Type == TEXT("done"))
    {
        // Assemble the full response from accumulated tokens + done metadata.
        FNpcDialogueResponse Response;
        Response.NpcResponse = AccumulatedTokens;
        AccumulatedTokens.Empty();

        const TSharedPtr<FJsonObject>* DoneData = nullptr;
        if (Msg->TryGetObjectField(TEXT("data"), DoneData) && DoneData)
        {
            FString DegLevel;
            (*DoneData)->TryGetStringField(TEXT("degradation_level"), DegLevel);
            Response.DegradationLevel = DegLevel;

            FString Emotion;
            (*DoneData)->TryGetStringField(TEXT("emotion"), Emotion);
            Response.Emotion = Emotion;

            // relation_deltas
            {
                const TSharedPtr<FJsonObject>* Deltas = nullptr;
                if ((*DoneData)->TryGetObjectField(TEXT("relation_deltas"), Deltas) && Deltas)
                {
                    (*Deltas)->TryGetNumberField(TEXT("trust"),     Response.RelationDeltas.Trust);
                    (*Deltas)->TryGetNumberField(TEXT("fear"),      Response.RelationDeltas.Fear);
                    (*Deltas)->TryGetNumberField(TEXT("affection"), Response.RelationDeltas.Affection);
                }
            }

            // action
            {
                const TSharedPtr<FJsonObject>* ActionObj = nullptr;
                if ((*DoneData)->TryGetObjectField(TEXT("action"), ActionObj) && ActionObj)
                {
                    FString ActionType;
                    (*ActionObj)->TryGetStringField(TEXT("type"), ActionType);
                    Response.Action.Type = FNpcEngineJsonUtils::ActionTypeFromString(ActionType);
                }
            }

            // facial_expression
            {
                const TSharedPtr<FJsonObject>* FaceObj = nullptr;
                if ((*DoneData)->TryGetObjectField(TEXT("facial_expression"), FaceObj) && FaceObj)
                {
                    FString FaceType;
                    (*FaceObj)->TryGetStringField(TEXT("type"), FaceType);
                    Response.FacialExpression.Type = FNpcEngineJsonUtils::FacialExpressionFromString(FaceType);
                    (*FaceObj)->TryGetNumberField(TEXT("intensity"), Response.FacialExpression.Intensity);
                }
            }

            // TODO(TTS): audio_bytes_b64
            FString AudioB64;
            if ((*DoneData)->TryGetStringField(TEXT("audio_bytes_b64"), AudioB64) && !AudioB64.IsEmpty())
            {
                FNpcEngineJsonUtils::ParseTTSAudio(AudioB64, Response.AudioBytes);
            }
        }

        if (OnDialogueComplete)
        {
            OnDialogueComplete(Response);
        }
    }
    else if (Type == TEXT("error"))
    {
        const FString ErrData = Msg->GetStringField(TEXT("data"));
        UE_LOG(LogNpcEngine, Warning, TEXT("WsClient: server error: %s"), *ErrData);
        if (OnDialogueError)
        {
            OnDialogueError(ErrData);
        }
    }
    else if (Type == TEXT("proactive_line"))
    {
        // Slice-1: ignore NPC-initiated push messages.
        UE_LOG(LogNpcEngine, Verbose, TEXT("WsClient: proactive_line received (ignored in slice-1)."));
    }
    else
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("WsClient: unknown message type '%s'."), *Type);
    }
}
