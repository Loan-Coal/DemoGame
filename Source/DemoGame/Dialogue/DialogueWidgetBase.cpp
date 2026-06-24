// File: DialogueWidgetBase.cpp
// Module: Game
// Purpose: Per-NPC dialogue widget — input lock, thinking indicator, memories badge, history display.
// Net I/O: no

#include "DialogueWidgetBase.h"
#include "DialogueManager.h"
#include "MemoryBadgeLookupAsset.h"
#include "NpcActorBase.h"
#include "NpcEngineTypes.h"
#include "DemoGame.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UDialogueWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;

    if (!DM)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("DialogueWidgetBase: DialogueManagerSubsystem not found."));
        return;
    }

    DM->OnNpcSpoke.AddDynamic(this, &UDialogueWidgetBase::OnNpcSpoke);
    DM->OnDialogueError.AddDynamic(this, &UDialogueWidgetBase::OnNpcError);
    DM->OnDialogueBegun.AddDynamic(this, &UDialogueWidgetBase::OnBegun);
    DM->OnDialogueEnded.AddDynamic(this, &UDialogueWidgetBase::OnEnded);
    DM->OnNpcMemoriesRecalled.AddDynamic(this, &UDialogueWidgetBase::OnMemoriesRecalledHandler);
}

void UDialogueWidgetBase::NativeDestruct()
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(MemoriesBadgeTimerHandle);
    }

    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;
    if (DM)
    {
        DM->OnNpcSpoke.RemoveDynamic(this, &UDialogueWidgetBase::OnNpcSpoke);
        DM->OnDialogueError.RemoveDynamic(this, &UDialogueWidgetBase::OnNpcError);
        DM->OnDialogueBegun.RemoveDynamic(this, &UDialogueWidgetBase::OnBegun);
        DM->OnDialogueEnded.RemoveDynamic(this, &UDialogueWidgetBase::OnEnded);
        DM->OnNpcMemoriesRecalled.RemoveDynamic(this, &UDialogueWidgetBase::OnMemoriesRecalledHandler);
    }

    Super::NativeDestruct();
}

void UDialogueWidgetBase::SubmitInput()
{
    FText InputFText;
    if (InputText)
    {
        InputFText = InputText->GetText();
    }
    const FString Message = InputFText.ToString().TrimStartAndEnd();

    if (Message.IsEmpty())
    {
        OnDialogueError(TEXT("Please type a message before sending."));
        return;
    }
    if (Message.Len() > NpcEngine::MaxPlayerMessageChars)
    {
        OnDialogueError(FString::Printf(
            TEXT("Message too long (%d/%d chars). Please shorten it."),
            Message.Len(), NpcEngine::MaxPlayerMessageChars));
        return;
    }

    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;
    if (!DM)
    {
        UE_LOG(LogDemoGame, Error, TEXT("DialogueWidgetBase: no DialogueManagerSubsystem."));
        return;
    }

    if (InputText)
    {
        InputText->SetText(FText::GetEmpty());
    }

    LockInput();

    if (ThinkingIndicator)
    {
        ThinkingIndicator->SetVisibility(ESlateVisibility::HitTestInvisible);
    }

    DM->SubmitPlayerMessage(Message);
}

// ── Private helpers ───────────────────────────────────────────────────────────

void UDialogueWidgetBase::LockInput()
{
    if (InputText)
    {
        InputText->SetIsReadOnly(true);
    }
}

void UDialogueWidgetBase::UnlockInput()
{
    if (InputText)
    {
        InputText->SetIsReadOnly(false);
    }
    if (ThinkingIndicator)
    {
        ThinkingIndicator->SetVisibility(ESlateVisibility::Collapsed);
    }
}

// ── Private delegate handlers ────────────────────────────────────────────────

void UDialogueWidgetBase::OnNpcSpoke(const FString& Response, const FString& DisplayName)
{
    UnlockInput();
    OnNpcResponseReceived(Response, DisplayName);
}

void UDialogueWidgetBase::OnNpcError(const FString& Error)
{
    UnlockInput();
    OnDialogueError(Error);
}

void UDialogueWidgetBase::OnBegun(ANpcActorBase* Npc)
{
    UnlockInput();
    OnDialogueBegun(Npc);
}

void UDialogueWidgetBase::OnEnded()
{
    UnlockInput();
    OnDialogueEnded();
}

void UDialogueWidgetBase::OnMemoriesRecalledHandler(FName /*NpcId*/, TArray<FString> Memories)
{
    if (!MemoriesBadge || Memories.IsEmpty())
    {
        return;
    }

    // Show the first memory badge (greybox: one badge at a time).
    FText BadgeText;
    if (MemoryBadgeLookup)
    {
        BadgeText = MemoryBadgeLookup->GetBadgeText(FName(*Memories[0]));
    }
    if (BadgeText.IsEmpty())
    {
        BadgeText = FText::FromString(Memories[0]);
    }

    MemoriesBadge->SetText(BadgeText);
    MemoriesBadge->SetVisibility(ESlateVisibility::HitTestInvisible);

    if (UWorld* World = GetWorld())
    {
        TWeakObjectPtr<UDialogueWidgetBase> WeakThis = this;
        World->GetTimerManager().SetTimer(MemoriesBadgeTimerHandle,
            FTimerDelegate::CreateLambda([WeakThis]()
            {
                if (UDialogueWidgetBase* Self = WeakThis.Get())
                {
                    if (Self->MemoriesBadge)
                    {
                        Self->MemoriesBadge->SetVisibility(ESlateVisibility::Collapsed);
                    }
                }
            }),
            5.f, false);
    }
}

// ── BlueprintNativeEvent C++ defaults ────────────────────────────────────────

void UDialogueWidgetBase::OnDialogueBegun_Implementation(ANpcActorBase* /*Npc*/)
{
    SetVisibility(ESlateVisibility::Visible);
    if (ResponseText)
    {
        ResponseText->SetText(FText::GetEmpty());
    }
    if (MemoriesBadge)
    {
        MemoriesBadge->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UDialogueWidgetBase::OnNpcResponseReceived_Implementation(
    const FString& NpcResponse, const FString& NpcDisplayName)
{
    if (ResponseText)
    {
        // Append rather than replace so history accumulates in the scroll.
        const FString Current = ResponseText->GetText().ToString();
        const FString Separator = Current.IsEmpty() ? TEXT("") : TEXT("\n");
        ResponseText->SetText(FText::FromString(
            Current + Separator + NpcDisplayName + TEXT(": ") + NpcResponse));
    }
    UE_LOG(LogDemoGame, Log, TEXT("DialogueWidget | %s: %s"), *NpcDisplayName, *NpcResponse);
}

void UDialogueWidgetBase::OnDialogueError_Implementation(const FString& ErrorMessage)
{
    if (ResponseText)
    {
        const FString Current = ResponseText->GetText().ToString();
        const FString Separator = Current.IsEmpty() ? TEXT("") : TEXT("\n");
        ResponseText->SetText(FText::FromString(
            Current + Separator + TEXT("[!] ") + ErrorMessage));
    }
    UE_LOG(LogDemoGame, Warning, TEXT("DialogueWidget | error: %s"), *ErrorMessage);
}

void UDialogueWidgetBase::OnDialogueEnded_Implementation()
{
    SetVisibility(ESlateVisibility::Collapsed);
}
