#pragma once

#include "CoreMinimal.h"
#include "NpcEngineTypes.h"

class IWebSocket;

/**
 * WebSocket streaming client for GET /v1/ws/dialogue.
 *
 * BUILT BUT NOT WIRED IN SLICE-1 — slice-1 gameplay uses UNpcEngineRestClient.
 * This class is scaffolded and compiles; wire it to gameplay in a later slice.
 *
 * Protocol (server → client):
 *   { "type": "token",          "data": "<chunk>" }       — accumulate into response text
 *   { "type": "done",           "data": { ...metadata } } — terminates the turn
 *   { "type": "error",          "data": "msg" }           — then server closes 1011
 *   { "type": "proactive_line", ... }                     — NPC-initiated push; ignored in slice-1
 *
 * Auth: send Authorization: Bearer <key> on the WS handshake.
 * Max 5 concurrent connections per key.
 */
class NPCENGINECLIENT_API FNpcEngineWebSocketClient
{
public:
    FNpcEngineWebSocketClient() = default;
    ~FNpcEngineWebSocketClient();

    // Not copyable — owns the websocket connection.
    FNpcEngineWebSocketClient(const FNpcEngineWebSocketClient&) = delete;
    FNpcEngineWebSocketClient& operator=(const FNpcEngineWebSocketClient&) = delete;

    // ── Connection lifecycle ─────────────────────────────────────────────────

    /** Open the WS connection with bearer auth. Call before SendDialogueRequest. */
    void Connect(const FString& WsUrl, const FString& BearerToken);

    /** Send one DialogueRequest JSON message after Connect(). */
    void SendDialogueRequest(const FNpcDialogueRequest& Request);

    /** Close the connection. Safe to call even if not connected. */
    void Disconnect();

    bool IsConnected() const;

    // ── Delegates ────────────────────────────────────────────────────────────

    /** Fires for each "token" message — stream text to the UI progressively. */
    TFunction<void(const FString& /*Chunk*/)> OnDialogueChunk;

    /** Fires on "done" message — carries full metadata (relation deltas, emotion, etc.). */
    TFunction<void(const FNpcDialogueResponse& /*Response*/)> OnDialogueComplete;

    /** Fires on "error" message or unexpected close. */
    TFunction<void(const FString& /*Reason*/)> OnDialogueError;

private:
    void OnMessage(const FString& Message);
    void OnConnected();
    void OnConnectionError(const FString& Error);
    void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);

    TSharedPtr<IWebSocket> WebSocket;
    FString AccumulatedTokens;   // concatenate "token" chunks until "done"
};
