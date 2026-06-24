#include "NpcEngineJsonUtils.h"
#include "NpcEngineClient.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

// ── Enum conversion ──────────────────────────────────────────────────────────

ENpcActionType FNpcEngineJsonUtils::ActionTypeFromString(const FString& Str)
{
    if (Str == TEXT("speak"))  return ENpcActionType::Speak;
    if (Str == TEXT("move"))   return ENpcActionType::Move;
    if (Str == TEXT("give"))   return ENpcActionType::Give;
    if (Str == TEXT("take"))   return ENpcActionType::Take;
    if (Str == TEXT("attack")) return ENpcActionType::Attack;
    if (Str == TEXT("flee"))   return ENpcActionType::Flee;
    if (Str == TEXT("idle"))   return ENpcActionType::Idle;

    UE_LOG(LogNpcEngine, Warning,
        TEXT("Unknown NPC action type '%s', falling back to Speak for forward-compat."), *Str);
    return ENpcActionType::Speak;
}

ENpcFacialExpression FNpcEngineJsonUtils::FacialExpressionFromString(const FString& Str)
{
    if (Str == TEXT("neutral"))   return ENpcFacialExpression::Neutral;
    if (Str == TEXT("happy"))     return ENpcFacialExpression::Happy;
    if (Str == TEXT("sad"))       return ENpcFacialExpression::Sad;
    if (Str == TEXT("angry"))     return ENpcFacialExpression::Angry;
    if (Str == TEXT("fearful"))   return ENpcFacialExpression::Fearful;
    if (Str == TEXT("surprised")) return ENpcFacialExpression::Surprised;
    if (Str == TEXT("disgusted")) return ENpcFacialExpression::Disgusted;
    if (Str == TEXT("contempt"))  return ENpcFacialExpression::Contempt;

    UE_LOG(LogNpcEngine, Warning,
        TEXT("Unknown facial expression '%s', falling back to Neutral for forward-compat."), *Str);
    return ENpcFacialExpression::Neutral;
}

// ── Deserialisation ──────────────────────────────────────────────────────────

bool FNpcEngineJsonUtils::ParseDialogueResponse(const FString& JsonBody, FNpcDialogueResponse& Out)
{
    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonBody);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("ParseDialogueResponse: failed to parse JSON body."));
        return false;
    }

    Out.NpcResponse = Root->GetStringField(TEXT("npc_response"));
    Out.MoodUpdate  = Root->GetStringField(TEXT("mood_update"));
    Out.Emotion     = Root->GetStringField(TEXT("emotion"));
    Out.SessionId   = Root->GetStringField(TEXT("session_id"));
    Out.DegradationLevel = Root->GetStringField(TEXT("degradation_level"));
    Root->TryGetBoolField(TEXT("cached"), Out.bCached);

    // relation_deltas
    {
        const TSharedPtr<FJsonObject>* DeltasObj = nullptr;
        if (Root->TryGetObjectField(TEXT("relation_deltas"), DeltasObj) && DeltasObj)
        {
            (*DeltasObj)->TryGetNumberField(TEXT("trust"),     Out.RelationDeltas.Trust);
            (*DeltasObj)->TryGetNumberField(TEXT("fear"),      Out.RelationDeltas.Fear);
            (*DeltasObj)->TryGetNumberField(TEXT("affection"), Out.RelationDeltas.Affection);
        }
    }

    // action
    {
        const TSharedPtr<FJsonObject>* ActionObj = nullptr;
        if (Root->TryGetObjectField(TEXT("action"), ActionObj) && ActionObj)
        {
            FString TypeStr;
            (*ActionObj)->TryGetStringField(TEXT("type"), TypeStr);
            Out.Action.Type = ActionTypeFromString(TypeStr);
            (*ActionObj)->TryGetStringField(TEXT("target_id"), Out.Action.TargetId);

            // Serialise parameters back to string for forward-compat storage.
            const TSharedPtr<FJsonObject>* ParamsObj = nullptr;
            if ((*ActionObj)->TryGetObjectField(TEXT("parameters"), ParamsObj) && ParamsObj)
            {
                FString ParamsStr;
                TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ParamsStr);
                FJsonSerializer::Serialize((*ParamsObj).ToSharedRef(), Writer);
                Out.Action.ParametersJson = ParamsStr;
            }
        }
    }

    // facial_expression
    {
        const TSharedPtr<FJsonObject>* FaceObj = nullptr;
        if (Root->TryGetObjectField(TEXT("facial_expression"), FaceObj) && FaceObj)
        {
            FString FaceTypeStr;
            (*FaceObj)->TryGetStringField(TEXT("type"), FaceTypeStr);
            Out.FacialExpression.Type = FacialExpressionFromString(FaceTypeStr);
            (*FaceObj)->TryGetNumberField(TEXT("intensity"), Out.FacialExpression.Intensity);
        }
    }

    // arrays
    {
        const TArray<TSharedPtr<FJsonValue>>* FactsArr = nullptr;
        if (Root->TryGetArrayField(TEXT("learned_facts"), FactsArr))
        {
            for (const TSharedPtr<FJsonValue>& Val : *FactsArr)
            {
                Out.LearnedFacts.Add(Val->AsString());
            }
        }
    }
    {
        const TArray<TSharedPtr<FJsonValue>>* MemArr = nullptr;
        if (Root->TryGetArrayField(TEXT("memories_recalled"), MemArr))
        {
            for (const TSharedPtr<FJsonValue>& Val : *MemArr)
            {
                Out.MemoriesRecalled.Add(Val->AsString());
            }
        }
    }

    // audio_bytes — over REST this is null/unreliable (raw bytes aren't UTF-8).
    // TODO(TTS): over WS the done message carries audio_bytes_b64 — decode there.

    return !Out.NpcResponse.IsEmpty();
}

bool FNpcEngineJsonUtils::UnwrapEnvelopeData(const FString& JsonBody, TSharedPtr<FJsonObject>& OutData)
{
    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonBody);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        return false;
    }

    // Non-null .error = failure even on HTTP 200.
    const TSharedPtr<FJsonObject>* ErrorObj = nullptr;
    if (Root->TryGetObjectField(TEXT("error"), ErrorObj) && ErrorObj && ErrorObj->IsValid())
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("OkEnvelope has non-null error field."));
        return false;
    }

    const TSharedPtr<FJsonObject>* DataObj = nullptr;
    if (!Root->TryGetObjectField(TEXT("data"), DataObj) || !DataObj)
    {
        // data can also be null (e.g. node not found).
        return false;
    }
    OutData = *DataObj;
    return true;
}

// ── Serialisation ────────────────────────────────────────────────────────────

FString FNpcEngineJsonUtils::SerialiseDialogueRequest(const FNpcDialogueRequest& Req)
{
    TSharedRef<FJsonObject> Obj = MakeShared<FJsonObject>();
    Obj->SetStringField(TEXT("player_id"),      Req.PlayerId);
    Obj->SetStringField(TEXT("npc_id"),         Req.NpcId);
    Obj->SetStringField(TEXT("player_message"), Req.PlayerMessage);

    if (!Req.LocationId.IsEmpty())
        Obj->SetStringField(TEXT("location_id"), Req.LocationId);
    if (!Req.SessionId.IsEmpty())
        Obj->SetStringField(TEXT("session_id"),  Req.SessionId);

    TArray<TSharedPtr<FJsonValue>> NodeIds;
    for (const FString& Id : Req.ExplicitNodeIds)
        NodeIds.Add(MakeShared<FJsonValueString>(Id));
    Obj->SetArrayField(TEXT("explicit_node_ids"), NodeIds);

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Obj, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseActionReportRequest(const FNpcActionReportRequest& Req)
{
    TSharedRef<FJsonObject> Obj = MakeShared<FJsonObject>();
    Obj->SetStringField(TEXT("action_type"), Req.ActionType);
    Obj->SetStringField(TEXT("player_id"),   Req.PlayerId);
    Obj->SetStringField(TEXT("npc_id"),      Req.NpcId);
    if (Req.Intensity != 0)
        Obj->SetNumberField(TEXT("intensity"), Req.Intensity);
    if (!Req.CounterpartyId.IsEmpty())
        Obj->SetStringField(TEXT("counterparty_id"), Req.CounterpartyId);
    if (Req.CurrencyAmount != 0)
        Obj->SetNumberField(TEXT("currency_amount"), Req.CurrencyAmount);
    if (!Req.SessionScope.IsEmpty())
        Obj->SetStringField(TEXT("session_scope"), Req.SessionScope);
    if (!Req.CurrencyReason.IsEmpty())
        Obj->SetStringField(TEXT("currency_reason"), Req.CurrencyReason);

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Obj, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseNodeWrite(const FString& PropertiesJson)
{
    // Wrap pre-serialised properties in { "properties": <obj> }
    TSharedPtr<FJsonObject> PropsObj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(PropertiesJson);
    if (!FJsonSerializer::Deserialize(Reader, PropsObj) || !PropsObj.IsValid())
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("SerialiseNodeWrite: invalid PropertiesJson — using empty object."));
        PropsObj = MakeShared<FJsonObject>();
    }

    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetObjectField(TEXT("properties"), PropsObj);

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseEdgeWrite(
    const FString& SrcId,
    const FString& DstId,
    const FString& PropertiesJson)
{
    TSharedPtr<FJsonObject> PropsObj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(PropertiesJson);
    if (!FJsonSerializer::Deserialize(Reader, PropsObj) || !PropsObj.IsValid())
    {
        PropsObj = MakeShared<FJsonObject>();
    }

    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("src_id"), SrcId);
    Root->SetStringField(TEXT("dst_id"), DstId);
    Root->SetObjectField(TEXT("properties"), PropsObj);

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseClockAdvance(int32 DeltaTicks)
{
    TSharedRef<FJsonObject> Obj = MakeShared<FJsonObject>();
    Obj->SetNumberField(TEXT("delta_ticks"), DeltaTicks);

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Obj, Writer);
    return Out;
}

// ── Quest lifecycle serialisation (DEC-027) ──────────────────────────────────

FString FNpcEngineJsonUtils::SerialiseQuestOffer(const FQuestOfferRequest& Req)
{
    TArray<TSharedPtr<FJsonValue>> ObjArr;
    for (const FQuestObjectiveData& O : Req.Objectives)
    {
        TSharedRef<FJsonObject> ObjEl = MakeShared<FJsonObject>();
        ObjEl->SetStringField(TEXT("objective_id"),       O.ObjectiveId);
        ObjEl->SetStringField(TEXT("description"),        O.Description);
        ObjEl->SetNumberField(TEXT("required_progress"),  O.RequiredProgress);
        ObjArr.Add(MakeShared<FJsonValueObject>(ObjEl));
    }

    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("quest_id"),   Req.QuestId);
    Root->SetStringField(TEXT("player_id"),  Req.PlayerId);
    Root->SetStringField(TEXT("title"),      Req.Title);
    Root->SetArrayField(TEXT("objectives"),  ObjArr);
    Root->SetArrayField(TEXT("item_rewards"), TArray<TSharedPtr<FJsonValue>>{});
    Root->SetField(TEXT("currency_reward"),  MakeShared<FJsonValueNull>());

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseQuestAccept(const FString& QuestId, const FString& PlayerId)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("quest_id"),  QuestId);
    Root->SetStringField(TEXT("player_id"), PlayerId);
    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseQuestObjective(const FQuestObjectiveRequest& Req)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("quest_id"),      Req.QuestId);
    Root->SetStringField(TEXT("player_id"),     Req.PlayerId);
    Root->SetStringField(TEXT("objective_id"),  Req.ObjectiveId);
    Root->SetNumberField(TEXT("progress_delta"),Req.ProgressDelta);
    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseQuestEvaluate(const FString& QuestId, const FString& PlayerId)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("quest_id"),  QuestId);
    Root->SetStringField(TEXT("player_id"), PlayerId);
    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseQuestReward(const FString& QuestId, const FString& PlayerId)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("quest_id"),  QuestId);
    Root->SetStringField(TEXT("player_id"), PlayerId);
    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

FString FNpcEngineJsonUtils::SerialiseQuestChoose(const FString& PlayerId, const FString& ChoiceId)
{
    // quest_id goes in the URL path — body contains only player_id and choice_id (DEC-027).
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("player_id"), PlayerId);
    Root->SetStringField(TEXT("choice_id"), ChoiceId);
    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    return Out;
}

// ── TTS stub ─────────────────────────────────────────────────────────────────

bool FNpcEngineJsonUtils::ParseTTSAudio(const FString& /*Base64Wav*/, TArray<uint8>& Out)
{
    // TODO(TTS): Decode Base64Wav → raw WAV bytes → PCM for USoundWaveProcedural.
    // 1. FBase64::Decode(Base64Wav, Out)
    // 2. Strip WAV header, extract PCM samples.
    // 3. Feed to USoundWaveProcedural via QueueAudio().
    Out.Empty();
    return false;
}
