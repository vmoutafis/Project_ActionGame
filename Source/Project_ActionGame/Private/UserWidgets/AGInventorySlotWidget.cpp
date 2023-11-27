// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGInventorySlotWidget.h"

#include "AGHelperFunctions.h"
#include "Components/Image.h"
#include "Loot/AGLoot.h"

UAGInventorySlotWidget::UAGInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IMG_Border = nullptr;
	IMG_Icon = nullptr;
	Item = FInventoryItem();
	HighlightTint = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
	NormalTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	bDebugHighlight = false;
	InventoryIndex = -1;
}

void UAGInventorySlotWidget::SetSlot(const FInventoryItem* NewItem, const int& Index)
{
	InventoryIndex = Index;
	
	if (NewItem == nullptr)
	{
		Item.Clear();
		NormalTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		Item = *NewItem;
		NormalTint = UAGHelperFunctions::GetRarityColour(NewItem->Rarity);
	}

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

FReply UAGInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	if (!InMouseEvent.IsMouseButtonDown(FKey(EKeys::LeftMouseButton)))
		return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	
	if (InventoryIndex < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No inventory index assigned to slot."))
		return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	}

	if (Item.bIsEmpty)
		return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	
	Delegate_OnActivated.Broadcast(InventoryIndex);
	
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
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
	IMG_Border->SetColorAndOpacity(NormalTint);
	
	if (Item.bIsEmpty)
	{
		IMG_Icon->SetBrushFromTexture(nullptr);
		IMG_Icon->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	IMG_Icon->SetBrushFromTexture(Item.LootClass.GetDefaultObject()->Icon);
	IMG_Icon->SetVisibility(ESlateVisibility::Visible);
	
	if (!HasAnyUserFocus() && !IsHovered())
		return;

	EnableHighlight(true);
}
