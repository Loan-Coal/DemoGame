// File: RumorJournalWidget.h
// Module: DemoGame
// Purpose: C++ base class for the Tab-key Rumor Journal UMG widget.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "World/GossipCacheSubsystem.h"
#include "RumorJournalWidget.generated.h"

class UScrollBox;
class UVerticalBox;

/**
 * C++ base class for the Rumor Journal (Tab key).
 *
 * Reads from UGossipCacheSubsystem on open. Widget layout (chain card rows, distortion badges)
 * is authored in the WBP_RumorJournal Blueprint subclass — editor session task.
 *
 * Each chain card row is only visible when bPlayerSpokeToNpc == true for that hop's NPC.
 * Distortion badge labels: HopCount 0 → "Firsthand"; 1 → "Rumor"; 2+ → "Distorted".
 *
 * Layout: a legible default panel (header + ChainScrollBox/ChainContainer) is built in C++ when no
 * designer layout is present, and the C++ OnJournalRefreshed default populates one card per visible
 * hop — so the journal works with zero Blueprint. An authored WBP overrides both.
 */
UCLASS()
class DEMOGAME_API URumorJournalWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual TSharedRef<SWidget> RebuildWidget() override;

    /** Refresh from GossipCacheSubsystem. Called on widget open and on each tick advance. */
    UFUNCTION(BlueprintCallable, Category = "Journal")
    void RefreshJournal();

    /**
     * Override in Blueprint to populate chain card rows.
     * Only entries with bPlayerSpokeToNpc == true should be shown.
     * Distortion label: HopCount 0 → "Firsthand"; 1 → "Rumor"; 2+ → "Distorted".
     */
    UFUNCTION(BlueprintNativeEvent, Category = "Journal")
    void OnJournalRefreshed(const TArray<FGossipEntry>& AllEntries);

    /** Static helper: distortion badge label for a hop count. */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Journal")
    static FText GetDistortionLabel(int32 HopCount);

protected:
    /** Scrollable container for chain cards (optional — layout authored in Blueprint). */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UScrollBox> ChainScrollBox;

    /** Vertical box holding chain entries (optional — layout authored in Blueprint). */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UVerticalBox> ChainContainer;

private:
    /** Build the legible default panel when no designer layout exists. */
    void BuildDefaultTree();

    /** Construct one card widget for a visible gossip hop. */
    class UWidget* MakeChainCard(const FGossipEntry& Entry);
};
