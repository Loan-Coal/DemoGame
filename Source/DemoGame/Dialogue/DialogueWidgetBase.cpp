// File: DialogueWidgetBase.cpp
// Module: Game
// Purpose: Per-NPC dialogue widget — input lock, thinking indicator, memories badge, history display.
// Net I/O: no

#include "DialogueWidgetBase.h"
#include "DialogueManager.h"
#include "MemoryBadgeLookupAsset.h"
#include "MemoryBadgeDefaults.h"
#include "NpcActorBase.h"
#include "NpcEngineTypes.h"
#include "DemoGame.h"
#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
namespace
{
    // Greybox chat-panel metrics (slate units). Explicit width is what stops the tree from
    // shrink-wrapping to the Send button alone; the rest keep the reply/input areas visibly sized.
    constexpr float PanelWidth     = 820.f;
    constexpr float ReplyHeight    = 220.f;
    constexpr float PanelBottomPad = 24.f;   // lift the panel off the screen's bottom edge
}

TSharedRef<SWidget> UDialogueWidgetBase::RebuildWidget()
{
    // C++ owns the greybox dialogue layout (DEC: C++-authoritative dialogue UI).
    // A WBP_Dialogue Blueprint subclass ships an authored designer tree, which would make
    // WidgetTree->RootWidget non-null and silently suppress BuildDefaultTree(). We discard
    // any such tree so the bottom-centre panel built here is always what renders, regardless
    // of the Blueprint. Re-enable Blueprint layout by gating this on a flag if art lands.
    if (WidgetTree)
    {
        WidgetTree->RootWidget = nullptr;
        BuildDefaultTree();
    }
    return Super::RebuildWidget();
}

void UDialogueWidgetBase::BuildDefaultTree()
{
    // UOverlay as root gives explicit, reliable slot alignment for each layer.
    // UBorderSlot defaults (HAlign_Fill, VAlign_Fill) would override content-alignment set on a
    // UBorder root, causing the panel to stretch to fill the whole viewport instead of sitting
    // at bottom-centre. UOverlaySlot alignment is primary and never overridden.
    UOverlay* Root = WidgetTree->ConstructWidget<UOverlay>();
    WidgetTree->RootWidget = Root;

    // Chat panel: 820px wide, bottom-centred, floating above the screen edge.
    // No dim backdrop — the game world stays fully visible.
    USizeBox* PanelSize = WidgetTree->ConstructWidget<USizeBox>();
    PanelSize->SetWidthOverride(PanelWidth);
    if (UOverlaySlot* PanelSlot = Root->AddChildToOverlay(PanelSize))
    {
        PanelSlot->SetHorizontalAlignment(HAlign_Center);
        PanelSlot->SetVerticalAlignment(VAlign_Bottom);
        PanelSlot->SetPadding(FMargin(0.f, 0.f, 0.f, PanelBottomPad));
    }

    UBorder* Card = DemoUi::MakePanel(*WidgetTree, DemoUi::Panel);
    PanelSize->AddChild(Card);

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    Card->SetContent(Box);

    // Reply history: tinted backing panel + fixed height so the area is always visible.
    UBorder* ReplyBg = DemoUi::MakePanel(*WidgetTree, DemoUi::PanelHeader, DemoUi::PadRow);
    USizeBox* ScrollSize = WidgetTree->ConstructWidget<USizeBox>();
    ScrollSize->SetHeightOverride(ReplyHeight);
    ResponseScroll = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), TEXT("ResponseScroll"));
    ScrollSize->AddChild(ResponseScroll);
    ResponseText = DemoUi::MakeText(*WidgetTree, FText::GetEmpty(),
        DemoUi::FontBody, DemoUi::TextPrimary, ETextJustify::Left, TEXT("ResponseText"));
    ResponseScroll->AddChild(ResponseText);
    ReplyBg->SetContent(ScrollSize);
    if (UVerticalBoxSlot* ReplySlot = Box->AddChildToVerticalBox(ReplyBg))
    {
        ReplySlot->SetPadding(FMargin(0.f, 0.f, 0.f, DemoUi::PadRow));
    }

    // Status line: thinking indicator + memories badge (both hidden until used).
    ThinkingIndicator = DemoUi::MakeText(*WidgetTree, FText::FromString(TEXT("Thinking…")),
        DemoUi::FontSmall, DemoUi::TextMuted, ETextJustify::Left, TEXT("ThinkingIndicator"));
    ThinkingIndicator->SetVisibility(ESlateVisibility::Collapsed);
    Box->AddChildToVerticalBox(ThinkingIndicator);

    MemoriesBadge = DemoUi::MakeText(*WidgetTree, FText::GetEmpty(),
        DemoUi::FontSmall, DemoUi::TextAccent, ETextJustify::Left, TEXT("MemoriesBadge"));
    MemoriesBadge->SetVisibility(ESlateVisibility::Collapsed);
    Box->AddChildToVerticalBox(MemoriesBadge);

    // Input row: editable field (light bg for legible default text) + Send button.
    UHorizontalBox* InputRow = WidgetTree->ConstructWidget<UHorizontalBox>();
    if (UVerticalBoxSlot* RowSlot = Box->AddChildToVerticalBox(InputRow))
    {
        RowSlot->SetPadding(FMargin(0.f, DemoUi::PadRow, 0.f, 0.f));
    }

    UBorder* InputBg = DemoUi::MakePanel(*WidgetTree, DemoUi::InputBg, DemoUi::PadRow);
    InputText = WidgetTree->ConstructWidget<UEditableText>(UEditableText::StaticClass(), TEXT("InputText"));
    InputText->SetHintText(FText::FromString(TEXT("Type a message…")));
    InputBg->SetContent(InputText);
    if (UHorizontalBoxSlot* InputSlot = InputRow->AddChildToHorizontalBox(InputBg))
    {
        InputSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
        InputSlot->SetVerticalAlignment(VAlign_Center);
        InputSlot->SetPadding(FMargin(0.f, 0.f, DemoUi::PadRow, 0.f));
    }

    UTextBlock* SendLabel = nullptr;
    SendButton = DemoUi::MakeButton(*WidgetTree, FText::FromString(TEXT("Send")),
        SendLabel, TEXT("SendButton"));
    InputRow->AddChildToHorizontalBox(SendButton);
}

void UDialogueWidgetBase::OnSendClicked()
{
    SubmitInput();
}

void UDialogueWidgetBase::OnInputCommitted(const FText& /*Text*/, ETextCommit::Type CommitMethod)
{
    if (CommitMethod == ETextCommit::OnEnter)
    {
        SubmitInput();
    }
}

void UDialogueWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    if (SendButton)
    {
        SendButton->OnClicked.AddDynamic(this, &UDialogueWidgetBase::OnSendClicked);
    }
    if (InputText)
    {
        InputText->OnTextCommitted.AddDynamic(this, &UDialogueWidgetBase::OnInputCommitted);
    }

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

    // Echo the player's own line into the history so the panel reads as a back-and-forth
    // (the engine only returns the NPC's reply; the player turn is shown locally).
    AppendHistory(FString::Printf(TEXT("You: %s"), *Message));

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

void UDialogueWidgetBase::AppendHistory(const FString& Line)
{
    if (!ResponseText)
    {
        return;
    }
    const FString Current = ResponseText->GetText().ToString();
    const FString Separator = Current.IsEmpty() ? TEXT("") : TEXT("\n");
    ResponseText->SetText(FText::FromString(Current + Separator + Line));
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
    // Lookup priority: DA_MemoryBadgeLookup DataAsset → C++ stubs (MemoryBadgeDefaults) → raw ID.
    FText BadgeText;
    const FName MemoryKey(*Memories[0]);
    if (MemoryBadgeLookup)
    {
        BadgeText = MemoryBadgeLookup->GetBadgeText(MemoryKey);
    }
    if (BadgeText.IsEmpty())
    {
        BadgeText = MemoryBadgeDefaults::GetBadgeText(MemoryKey);
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
    // Append rather than replace so history accumulates in the scroll.
    AppendHistory(NpcDisplayName + TEXT(": ") + NpcResponse);
    UE_LOG(LogDemoGame, Log, TEXT("DialogueWidget | %s: %s"), *NpcDisplayName, *NpcResponse);
}

void UDialogueWidgetBase::OnDialogueError_Implementation(const FString& ErrorMessage)
{
    AppendHistory(TEXT("[!] ") + ErrorMessage);
    UE_LOG(LogDemoGame, Warning, TEXT("DialogueWidget | error: %s"), *ErrorMessage);
}

void UDialogueWidgetBase::OnDialogueEnded_Implementation()
{
    SetVisibility(ESlateVisibility::Collapsed);
}
