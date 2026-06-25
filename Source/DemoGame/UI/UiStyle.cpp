// File: UiStyle.cpp
// Module: Game
// Purpose: Shared colors/metrics + UMG construction helpers so C++-built widgets are legible.
// Net I/O: no

#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/ButtonSlot.h"
#include "Components/BorderSlot.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Fonts/SlateFontInfo.h"

namespace
{
    /** A solid color fill brush (engine white box tinted to the requested color). */
    FSlateBrush SolidBrush(const FLinearColor& Color)
    {
        FSlateBrush Brush;
        Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
        Brush.TintColor = FSlateColor(Color);
        Brush.OutlineSettings.CornerRadii = FVector4(4.f, 4.f, 4.f, 4.f);
        Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
        return Brush;
    }
}

namespace DemoUi
{
    UTextBlock* MakeText(UWidgetTree& Tree, const FText& Text, int32 FontSize,
        const FSlateColor& Color, ETextJustify::Type Justify, FName Name)
    {
        UTextBlock* Block = Tree.ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), Name);
        Block->SetText(Text);
        Block->SetColorAndOpacity(Color);
        Block->SetJustification(Justify);
        Block->SetAutoWrapText(true);

        FSlateFontInfo Font = Block->GetFont();
        Font.Size = FontSize;
        Block->SetFont(Font);
        return Block;
    }

    UBorder* MakePanel(UWidgetTree& Tree, const FLinearColor& Fill, float Padding, FName Name)
    {
        UBorder* PanelBorder = Tree.ConstructWidget<UBorder>(UBorder::StaticClass(), Name);
        PanelBorder->SetBrushColor(Fill);
        PanelBorder->SetPadding(FMargin(Padding));
        return PanelBorder;
    }

    UBorder* MakeBackdrop(UWidgetTree& Tree, bool bDim,
        EHorizontalAlignment HAlign, EVerticalAlignment VAlign, FName Name)
    {
        UBorder* Root = Tree.ConstructWidget<UBorder>(UBorder::StaticClass(), Name);
        Root->SetBrushColor(bDim ? Backdrop : FLinearColor::Transparent);
        Root->SetPadding(FMargin(bDim ? 0.f : PadCard));
        Root->SetHorizontalAlignment(HAlign);
        Root->SetVerticalAlignment(VAlign);
        return Root;
    }

    void StyleButton(UButton& Button)
    {
        FButtonStyle Style;
        Style.SetNormal(SolidBrush(ButtonNormal));
        Style.SetHovered(SolidBrush(ButtonHovered));
        Style.SetPressed(SolidBrush(ButtonPressed));
        Style.SetDisabled(SolidBrush(ButtonPressed));
        Style.NormalPadding = ButtonContentPadding;
        Style.PressedPadding = ButtonContentPadding;
        Button.SetStyle(Style);
    }

    UButton* MakeButton(UWidgetTree& Tree, const FText& Label,
        UTextBlock*& OutLabel, FName ButtonName, FName LabelName)
    {
        UButton* Button = Tree.ConstructWidget<UButton>(UButton::StaticClass(), ButtonName);
        StyleButton(*Button);

        OutLabel = MakeText(Tree, Label, FontButton, TextPrimary, ETextJustify::Center, LabelName);
        if (UButtonSlot* LabelSlot = Cast<UButtonSlot>(Button->AddChild(OutLabel)))
        {
            LabelSlot->SetHorizontalAlignment(HAlign_Center);
            LabelSlot->SetVerticalAlignment(VAlign_Center);
        }
        return Button;
    }
}
