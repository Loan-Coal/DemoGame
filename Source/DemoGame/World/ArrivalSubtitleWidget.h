// File: ArrivalSubtitleWidget.h
// Module: DemoGame
// Purpose: UMG base widget that shows a location arrival subtitle for 3 s on tick advance.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArrivalSubtitleWidget.generated.h"

class ULocationSubtitleData;
class UNpcWorldSubsystem;
class UTextBlock;
class UWidgetAnimation;

/**
 * HUD widget that listens to UNpcWorldSubsystem::OnTickAdvanced and shows authored
 * location subtitle text for 3 seconds, then fades via a UWidgetAnimation.
 *
 * Usage:
 *  1. Create WBP_ArrivalSubtitle (subclass of this widget) in the editor.
 *  2. Assign SubtitleData (a DA_LocationSubtitles DataAsset) on the widget defaults.
 *  3. Add a UTextBlock named SubtitleText and a UWidgetAnimation named FadeOutAnimation.
 *  4. Add to the player HUD.
 *
 * The widget hides itself after FadeOutAnimation completes or after SubtitleDisplaySeconds
 * if no animation is assigned.
 */
UCLASS(Abstract)
class DEMOGAME_API UArrivalSubtitleWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** DataAsset supplying per-location FText. Assign in the editor. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subtitle")
    TObjectPtr<ULocationSubtitleData> SubtitleData;

    /** How long the subtitle stays visible before the fade starts (seconds). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subtitle")
    float SubtitleDisplaySeconds = 3.f;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    /** BindWidget slot — must exist in the Blueprint subclass. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> SubtitleText;

    /** Optional fade-out animation. Play it on tick advance; hide when it finishes. */
    UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
    TObjectPtr<UWidgetAnimation> FadeOutAnimation;

private:
    UFUNCTION()
    void OnTickAdvanced(FName NewLocationId, int32 TickCount);

    void ShowSubtitle(FText Text);
    void HideSubtitle();

    FTimerHandle HideTimer;
};
