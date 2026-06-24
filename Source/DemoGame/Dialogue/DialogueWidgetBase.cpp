#include "DialogueWidgetBase.h"
#include "DialogueManager.h"
#include "NpcActorBase.h"
#include "DemoGame.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

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

    // Bind to subsystem delegates so the widget stays in sync (dynamic multicast → AddDynamic).
    DM->OnNpcSpoke.AddDynamic(this, &UDialogueWidgetBase::OnNpcSpoke);
    DM->OnDialogueError.AddDynamic(this, &UDialogueWidgetBase::OnNpcError);
    DM->OnDialogueBegun.AddDynamic(this, &UDialogueWidgetBase::OnBegun);
    DM->OnDialogueEnded.AddDynamic(this, &UDialogueWidgetBase::OnEnded);
}

void UDialogueWidgetBase::NativeDestruct()
{
    // Unbind delegates to prevent dangling callbacks.
    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;
    if (DM)
    {
        DM->OnNpcSpoke.RemoveDynamic(this, &UDialogueWidgetBase::OnNpcSpoke);
        DM->OnDialogueError.RemoveDynamic(this, &UDialogueWidgetBase::OnNpcError);
        DM->OnDialogueBegun.RemoveDynamic(this, &UDialogueWidgetBase::OnBegun);
        DM->OnDialogueEnded.RemoveDynamic(this, &UDialogueWidgetBase::OnEnded);
    }

    Super::NativeDestruct();
}

void UDialogueWidgetBase::SubmitInput()
{
    // Read from the bound UMG widget slot if available.
    FText InputFText;
    if (InputText)
    {
        InputFText = InputText->GetText();
    }
    const FString Message = InputFText.ToString().TrimStartAndEnd();

    // Client-side validation mirrors the engine contract (§1).
    if (Message.IsEmpty())
    {
        OnDialogueError(TEXT("Please type a message before sending."));
        return;
    }
    if (Message.Len() > MaxPlayerMessageChars)
    {
        OnDialogueError(FString::Printf(
            TEXT("Message too long (%d/%d chars). Please shorten it."),
            Message.Len(), MaxPlayerMessageChars));
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

    // Clear the input field immediately for responsiveness.
    if (InputText)
    {
        InputText->SetText(FText::GetEmpty());
    }

    DM->SubmitPlayerMessage(Message);
}

// ── Private delegate handlers ────────────────────────────────────────────────

void UDialogueWidgetBase::OnNpcSpoke(const FString& Response, const FString& DisplayName)
{
    OnNpcResponseReceived(Response, DisplayName);
}

void UDialogueWidgetBase::OnNpcError(const FString& Error)
{
    OnDialogueError(Error);
}

void UDialogueWidgetBase::OnBegun(ANpcActorBase* Npc)
{
    OnDialogueBegun(Npc);
}

void UDialogueWidgetBase::OnEnded()
{
    OnDialogueEnded();
}

// ── BlueprintNativeEvent C++ defaults (a Blueprint subclass may override) ─────

void UDialogueWidgetBase::OnDialogueBegun_Implementation(ANpcActorBase* /*Npc*/)
{
    SetVisibility(ESlateVisibility::Visible);
    if (ResponseText)
    {
        ResponseText->SetText(FText::GetEmpty());
    }
}

void UDialogueWidgetBase::OnNpcResponseReceived_Implementation(const FString& NpcResponse, const FString& NpcDisplayName)
{
    if (ResponseText)
    {
        ResponseText->SetText(FText::FromString(FString::Printf(TEXT("%s: %s"), *NpcDisplayName, *NpcResponse)));
    }
    UE_LOG(LogDemoGame, Log, TEXT("DialogueWidget | %s: %s"), *NpcDisplayName, *NpcResponse);
}

void UDialogueWidgetBase::OnDialogueError_Implementation(const FString& ErrorMessage)
{
    if (ResponseText)
    {
        ResponseText->SetText(FText::FromString(ErrorMessage));
    }
    UE_LOG(LogDemoGame, Warning, TEXT("DialogueWidget | error: %s"), *ErrorMessage);
}

void UDialogueWidgetBase::OnDialogueEnded_Implementation()
{
    SetVisibility(ESlateVisibility::Collapsed);
}
