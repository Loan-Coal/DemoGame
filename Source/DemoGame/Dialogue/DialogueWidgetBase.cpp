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

    // Bind to subsystem delegates so the widget stays in sync.
    NpcSpokeHandle = DM->OnNpcSpoke.AddUObject(this, &UDialogueWidgetBase::OnNpcSpoke);
    ErrorHandle    = DM->OnDialogueError.AddUObject(this, &UDialogueWidgetBase::OnNpcError);
    BegunHandle    = DM->OnDialogueBegun.AddUObject(this, &UDialogueWidgetBase::OnBegun);
    EndedHandle    = DM->OnDialogueEnded.AddUObject(this, &UDialogueWidgetBase::OnEnded);
}

void UDialogueWidgetBase::NativeDestruct()
{
    // Unbind delegates to prevent dangling callbacks.
    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;
    if (DM)
    {
        DM->OnNpcSpoke.Remove(NpcSpokeHandle);
        DM->OnDialogueError.Remove(ErrorHandle);
        DM->OnDialogueBegun.Remove(BegunHandle);
        DM->OnDialogueEnded.Remove(EndedHandle);
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
