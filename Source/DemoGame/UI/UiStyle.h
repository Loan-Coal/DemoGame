// File: UiStyle.h
// Module: Game
// Purpose: Shared colors/metrics + UMG construction helpers so C++-built widgets are legible.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateColor.h"
#include "Layout/Margin.h"

class UWidgetTree;
class UTextBlock;
class UButton;
class UBorder;

/**
 * DemoUi — one place for the greybox UI look so every C++-constructed widget is consistent
 * and readable (solid dark panels, white text, dimmed-but-visible backdrop). No magic
 * numbers/colors scattered across widgets. Replaced wholesale when v2 designer assets land.
 */
namespace DemoUi
{
    // ── Colors ──────────────────────────────────────────────────────────────────
    inline const FLinearColor Backdrop   = FLinearColor(0.f, 0.f, 0.f, 0.6f);   // dim, game still visible
    inline const FLinearColor Panel      = FLinearColor(0.08f, 0.08f, 0.10f, 0.96f);
    inline const FLinearColor PanelHeader = FLinearColor(0.14f, 0.15f, 0.20f, 1.f);
    inline const FLinearColor ButtonNormal  = FLinearColor(0.18f, 0.20f, 0.28f, 1.f);
    inline const FLinearColor ButtonHovered = FLinearColor(0.26f, 0.30f, 0.40f, 1.f);
    inline const FLinearColor ButtonPressed = FLinearColor(0.12f, 0.14f, 0.20f, 1.f);
    inline const FLinearColor TextPrimary = FLinearColor(0.95f, 0.95f, 0.97f, 1.f);
    inline const FLinearColor TextMuted   = FLinearColor(0.70f, 0.72f, 0.78f, 1.f);
    inline const FLinearColor TextAccent  = FLinearColor(1.0f, 0.84f, 0.40f, 1.f);   // gold badges
    inline const FLinearColor InputBg     = FLinearColor(0.85f, 0.86f, 0.90f, 1.f);  // light field
    inline const FLinearColor TextOnLight = FLinearColor(0.05f, 0.05f, 0.07f, 1.f);  // input text on light field

    // ── Font sizes (pt) ─────────────────────────────────────────────────────────
    inline constexpr int32 FontTitle  = 24;
    inline constexpr int32 FontButton = 18;
    inline constexpr int32 FontBody   = 16;
    inline constexpr int32 FontSmall  = 13;

    // ── Metrics (slate units) ───────────────────────────────────────────────────
    inline constexpr float PadCard = 16.f;
    inline constexpr float PadRow  = 8.f;
    inline const FMargin ButtonContentPadding = FMargin(16.f, 10.f);

    // ── Construction helpers (own the new widget on the UserWidget's tree) ───────

    /** A styled text block. Justify defaults to left. */
    UTextBlock* MakeText(UWidgetTree& Tree, const FText& Text, int32 FontSize,
        const FSlateColor& Color, ETextJustify::Type Justify = ETextJustify::Left,
        FName Name = NAME_None);

    /** A solid-color panel (UBorder) with uniform inner padding. */
    UBorder* MakePanel(UWidgetTree& Tree, const FLinearColor& Fill, float Padding = PadCard,
        FName Name = NAME_None);

    /**
     * A full-screen root border. bDim=true paints the dimmed backdrop; false is transparent
     * (for HUD corners). Child alignment positions the single content widget.
     */
    UBorder* MakeBackdrop(UWidgetTree& Tree, bool bDim,
        EHorizontalAlignment HAlign, EVerticalAlignment VAlign, FName Name = NAME_None);

    /** A styled button wrapping a centered label. OutLabel receives the inner text block. */
    UButton* MakeButton(UWidgetTree& Tree, const FText& Label,
        UTextBlock*& OutLabel, FName ButtonName = NAME_None, FName LabelName = NAME_None);

    /** Apply the greybox button color style to an existing button. */
    void StyleButton(UButton& Button);
}
