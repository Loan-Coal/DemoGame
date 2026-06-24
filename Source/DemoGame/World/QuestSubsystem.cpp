// File: QuestSubsystem.cpp
// Module: DemoGame
// Purpose: Tracks active quests; routes lifecycle calls through INpcQuestService.
// Net I/O: no

#include "QuestSubsystem.h"
#include "NpcEngineServiceSubsystem.h"
#include "PlayerIdProvider.h"
#include "DemoGame.h"
#include "Engine/GameInstance.h"

// ── Greybox quest metadata (DEC-028) ─────────────────────────────────────────
// Titles and first-step objective ID indexed by quest FName constant.
// No DataAsset required for Phase 5 — authored here, finalised in Phase 9.

namespace
{
    struct FQuestMeta
    {
        const TCHAR* Title;
        const TCHAR* FirstObjectiveId;
        const TCHAR* FirstObjectiveDesc;
        const TCHAR* NextQuestId;   // empty = end of chain
    };

    static const TMap<FName, FQuestMeta>& GetQuestMetaMap()
    {
        static TMap<FName, FQuestMeta> Map = {
            { QuestId::FindWineMerchant,
              { TEXT("Find the Wine Merchant"),
                TEXT("speak_to_mira"),
                TEXT("Speak to Mira about the merchant in the market."),
                TEXT("deliver_amulet") } },
            { QuestId::DeliverAmulet,
              { TEXT("Deliver the Amulet"),
                TEXT("find_aldric"),
                TEXT("Locate Aldric in the market square."),
                TEXT("aldric_confession") } },
            { QuestId::AldricConfession,
              { TEXT("The Confession"),
                TEXT("confront_aldric"),
                TEXT("Confront Aldric about the amulet's origin."),
                TEXT("") } },
            { QuestId::PatrolDuty,
              { TEXT("Patrol Duty"),
                TEXT("report_to_sorn"),
                TEXT("Report to Captain Sorn at the guard barracks."),
                TEXT("captain_report") } },
            { QuestId::CaptainReport,
              { TEXT("Captain's Report"),
                TEXT("gather_intel"),
                TEXT("Gather intelligence on the northern garrison."),
                TEXT("") } },
            { QuestId::MissingGoods,
              { TEXT("Missing Goods"),
                TEXT("investigate_market"),
                TEXT("Investigate rumours of missing goods in the market."),
                TEXT("fence_confrontation") } },
            { QuestId::FenceConfrontation,
              { TEXT("The Fence"),
                TEXT("confront_lira"),
                TEXT("Confront Lira about the missing goods."),
                TEXT("") } },
        };
        return Map;
    }

    static FString GetPlayerId()
    {
        return FPlayerIdProvider::GetOrCreatePlayerId();
    }
}

// ── Lifecycle ────────────────────────────────────────────────────────────────

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogDemoGame, Log, TEXT("QuestSubsystem initialised."));
}

void UQuestSubsystem::Deinitialize()
{
    QuestService = nullptr;
    Super::Deinitialize();
}

void UQuestSubsystem::SetQuestService(TScriptInterface<INpcQuestService> InService)
{
    QuestService = InService;
}

INpcQuestService* UQuestSubsystem::ResolveQuestService()
{
    if (QuestService.GetInterface())
    {
        return QuestService.GetInterface();
    }

    const UWorld* World = GetWorld();
    UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
    if (UNpcEngineServiceSubsystem* SS =
            GI ? GI->GetSubsystem<UNpcEngineServiceSubsystem>() : nullptr)
    {
        QuestService = SS->GetQuestService();
        return QuestService.GetInterface();
    }

    UE_LOG(LogDemoGame, Error,
        TEXT("QuestSubsystem::ResolveQuestService: NpcEngineServiceSubsystem unavailable."));
    return nullptr;
}

// ── Public API ───────────────────────────────────────────────────────────────

void UQuestSubsystem::ActivateQuest(FName InQuestId)
{
    INpcQuestService* Service = ResolveQuestService();
    if (!Service)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("QuestSubsystem::ActivateQuest: no service — QuestId=%s skipped."),
            *InQuestId.ToString());
        return;
    }

    const FQuestMeta* Meta = GetQuestMetaMap().Find(InQuestId);
    if (!Meta)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("QuestSubsystem::ActivateQuest: no metadata for QuestId=%s."),
            *InQuestId.ToString());
    }

    const FString QuestIdStr = InQuestId.ToString();
    const FString PlayerId   = GetPlayerId();
    const FString Title      = Meta ? Meta->Title : TEXT("Quest");

    // Build offer request.
    FQuestOfferRequest OfferReq;
    OfferReq.QuestId  = QuestIdStr;
    OfferReq.PlayerId = PlayerId;
    OfferReq.Title    = Title;
    if (Meta)
    {
        FQuestObjectiveData FirstObj;
        FirstObj.ObjectiveId      = Meta->FirstObjectiveId;
        FirstObj.Description      = Meta->FirstObjectiveDesc;
        FirstObj.RequiredProgress = 1;
        OfferReq.Objectives.Add(FirstObj);
    }

    TWeakObjectPtr<UQuestSubsystem> WeakThis = this;

    Service->QuestOffer(OfferReq,
        [WeakThis, InQuestId, QuestIdStr, PlayerId](bool bOfferOk)
        {
            if (!bOfferOk)
            {
                UE_LOG(LogDemoGame, Warning,
                    TEXT("QuestSubsystem: QuestOffer failed QuestId=%s."), *QuestIdStr);
                return;
            }
            UQuestSubsystem* Self = WeakThis.Get();
            if (!Self) return;

            INpcQuestService* Svc = Self->ResolveQuestService();
            if (!Svc) return;

            Svc->QuestAccept(QuestIdStr, PlayerId,
                [WeakThis, InQuestId, QuestIdStr](bool bAcceptOk)
                {
                    if (!bAcceptOk)
                    {
                        UE_LOG(LogDemoGame, Warning,
                            TEXT("QuestSubsystem: QuestAccept failed QuestId=%s."), *QuestIdStr);
                        return;
                    }
                    UQuestSubsystem* Self = WeakThis.Get();
                    if (!Self) return;

                    FQuestStepState Step;
                    Step.QuestId    = QuestIdStr;
                    Step.bCompleted = false;
                    Self->ActiveSteps.Add(Step);

                    UE_LOG(LogDemoGame, Log,
                        TEXT("QuestSubsystem: quest activated QuestId=%s"), *QuestIdStr);
                    Self->OnQuestActivated.Broadcast(InQuestId);
                },
                FOnNpcEngineError::CreateLambda([QuestIdStr](const FString& Err)
                {
                    UE_LOG(LogDemoGame, Error,
                        TEXT("QuestSubsystem: QuestAccept error QuestId=%s Error=%s"),
                        *QuestIdStr, *Err);
                }));
        },
        FOnNpcEngineError::CreateLambda([QuestIdStr](const FString& Err)
        {
            UE_LOG(LogDemoGame, Error,
                TEXT("QuestSubsystem: QuestOffer error QuestId=%s Error=%s"),
                *QuestIdStr, *Err);
        }));
}

void UQuestSubsystem::CompleteStep(FName InQuestId, FName InStepId)
{
    INpcQuestService* Service = ResolveQuestService();
    if (!Service)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("QuestSubsystem::CompleteStep: no service — QuestId=%s StepId=%s skipped."),
            *InQuestId.ToString(), *InStepId.ToString());
        return;
    }

    const FString QuestIdStr = InQuestId.ToString();
    const FString StepIdStr  = InStepId.ToString();
    const FString PlayerId   = GetPlayerId();

    FQuestObjectiveRequest ObjReq;
    ObjReq.QuestId      = QuestIdStr;
    ObjReq.PlayerId     = PlayerId;
    ObjReq.ObjectiveId  = StepIdStr;
    ObjReq.ProgressDelta = 1;

    TWeakObjectPtr<UQuestSubsystem> WeakThis = this;

    Service->QuestObjective(ObjReq,
        [WeakThis, InQuestId, InStepId, QuestIdStr, StepIdStr, PlayerId](bool bObjOk)
        {
            if (!bObjOk)
            {
                UE_LOG(LogDemoGame, Warning,
                    TEXT("QuestSubsystem: QuestObjective failed QuestId=%s StepId=%s"),
                    *QuestIdStr, *StepIdStr);
                return;
            }
            UQuestSubsystem* Self = WeakThis.Get();
            if (!Self) return;

            INpcQuestService* Svc = Self->ResolveQuestService();
            if (!Svc) return;

            Svc->QuestEvaluate(QuestIdStr, PlayerId,
                [WeakThis, InQuestId, InStepId, QuestIdStr, StepIdStr, PlayerId](bool bComplete)
                {
                    UQuestSubsystem* Self = WeakThis.Get();
                    if (!Self) return;

                    // Mark step completed in local state.
                    for (FQuestStepState& Step : Self->ActiveSteps)
                    {
                        if (Step.QuestId == QuestIdStr)
                        {
                            Step.StepId     = StepIdStr;
                            Step.bCompleted = true;
                        }
                    }

                    UE_LOG(LogDemoGame, Log,
                        TEXT("QuestSubsystem: step completed QuestId=%s StepId=%s Complete=%d"),
                        *QuestIdStr, *StepIdStr, bComplete ? 1 : 0);
                    Self->OnStepCompleted.Broadcast(InQuestId, InStepId);

                    if (!bComplete) return;

                    INpcQuestService* Svc = Self->ResolveQuestService();
                    if (!Svc) return;

                    // Deliver reward, then activate chained quest if any.
                    Svc->QuestReward(QuestIdStr, PlayerId,
                        [WeakThis, QuestIdStr](bool bRewardOk)
                        {
                            UE_LOG(LogDemoGame, Log,
                                TEXT("QuestSubsystem: reward delivered QuestId=%s Ok=%d"),
                                *QuestIdStr, bRewardOk ? 1 : 0);
                            UQuestSubsystem* Self = WeakThis.Get();
                            if (!Self) return;

                            // Check if there's a chained quest.
                            const FName QN = FName(*QuestIdStr);
                            const FQuestMeta* Meta = GetQuestMetaMap().Find(QN);
                            if (Meta && Meta->NextQuestId && FCString::Strlen(Meta->NextQuestId) > 0)
                            {
                                Self->ActivateQuest(FName(Meta->NextQuestId));
                            }
                        },
                        FOnNpcEngineError::CreateLambda([QuestIdStr](const FString& Err)
                        {
                            UE_LOG(LogDemoGame, Error,
                                TEXT("QuestSubsystem: QuestReward error QuestId=%s Error=%s"),
                                *QuestIdStr, *Err);
                        }));
                },
                FOnNpcEngineError::CreateLambda([QuestIdStr](const FString& Err)
                {
                    UE_LOG(LogDemoGame, Error,
                        TEXT("QuestSubsystem: QuestEvaluate error QuestId=%s Error=%s"),
                        *QuestIdStr, *Err);
                }));
        },
        FOnNpcEngineError::CreateLambda([QuestIdStr, StepIdStr](const FString& Err)
        {
            UE_LOG(LogDemoGame, Error,
                TEXT("QuestSubsystem: QuestObjective error QuestId=%s StepId=%s Error=%s"),
                *QuestIdStr, *StepIdStr, *Err);
        }));
}
