// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGInventorySlotWidget.h"

#include "Components/Image.h"
#include "Loot/AGLoot.h"

UAGInventorySlotWidget::UAGInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IMG_Border = nullptr;
	IMG_Icon = nullptr;
	Item = FInventorySlot();
	HighlightTint = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
	NormalTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	bDebugHighlight = false;
}

void UAGInventorySlotWidget::SetSlot(const FInventoryItem* NewItem)
{
	if (NewItem == nullptr)
		Item.Clear();
	else
		Item = *NewItem;

	UpdateSlot();
}

void UAGInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot();
}

void UAGInventorySlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsDesignTime())
	{
		if (bDebugHighlight)
			IMG_Border->SetColorAndOpacity(HighlightTint);
		else
			IMG_Border->SetColorAndOpacity(NormalTint);
	}
}

void UAGInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	EnableHighlight(true);
}

void UAGInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	EnableHighlight(false);
}

FReply UAGInventorySlotWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	EnableHighlight(true);

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UAGInventorySlotWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
	
	EnableHighlight(false);
}

void UAGInventorySlotWidget::EnableHighlight(bool Enable)
{
	if (Enable && !Item.bIsEmpty)
	{
		IMG_Border->SetColorAndOpacity(HighlightTint);
		return;
	}

	IMG_Border->SetColorAndOpacity(NormalTint);
}

void UAGInventorySlotWidget::UpdateSlot()
{
	if (Item.bIsEmpty)
	{
		IMG_Icon->SetBrushFromTexture(nullptr);
		return;
	}

	IMG_Icon->SetBrushFromTexture(Item.Item.LootClass.GetDefaultObject()->Icon);

	if (!HasAnyUserFocus() && !IsHovered())
		return;

	EnableHighlight(true);
}
