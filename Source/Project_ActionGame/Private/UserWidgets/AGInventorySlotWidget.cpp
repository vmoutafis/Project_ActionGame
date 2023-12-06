// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGInventorySlotWidget.h"

#include "AGGameInstance.h"
#include "AGHelperFunctions.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Loot/AGDLootGearWeapon.h"
#include "Loot/AGLoot.h"
#include "UserWidgets/AGInventoryWidget.h"
#include "UserWidgets/DDOs/AGInventorySlotDDO.h"

UAGInventorySlotWidget::UAGInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IMG_Border = nullptr;
	IMG_Icon = nullptr;
	IMG_Highlight = nullptr;
	Item = FInventoryItem();
	HighlightTint = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
	NormalTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	bDebugHighlight = false;
	InventoryIndex = -1;
	InventoryWidget = nullptr;
}

void UAGInventorySlotWidget::SetSlot(UAGInventoryWidget* Widget, const FInventoryItem* NewItem, const int& Index)
{
	InventoryIndex = Index;
	InventoryWidget = Widget;
	
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

void UAGInventorySlotWidget::SetAsEquipmentSlot(TEnumAsByte<EGearType> DefaultGearType)
{
	Item.GearType = DefaultGearType;
}

void UAGInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot();
}

void UAGInventorySlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	IMG_Border->SetColorAndOpacity(NormalTint);
}

void UAGInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	EnableHighlight(true);

	EnableItemInfoWidget(true);
}

void UAGInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	EnableHighlight(false);

	EnableItemInfoWidget(false);
}

FReply UAGInventorySlotWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	EnableHighlight(true);

	EnableItemInfoWidget(true);

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UAGInventorySlotWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
	
	EnableHighlight(false);

	EnableItemInfoWidget(false);
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

	if (Item.GearType != EGearType::GT_None)
		return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());
	GI->ActivateInventoryItem(InventoryIndex);
	
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UAGInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UAGInventorySlotWidget* DragWidget = CreateWidget<UAGInventorySlotWidget>(GetWorld(), this->GetClass());
	DragWidget->SetSlot(InventoryWidget, &Item, InventoryIndex);

	UAGInventorySlotDDO* DragDrop = NewObject<UAGInventorySlotDDO>();
	DragDrop->WidgetRef = DragWidget;
	DragDrop->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDrop->DefaultDragVisual = DragWidget;
	DragDrop->Pivot = EDragPivot::CenterCenter;

	UpdateSlot(true);
	
	OutOperation = DragDrop;
}

void UAGInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UpdateSlot();
}

FReply UAGInventorySlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	if (Item.bIsEmpty)
		return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	
	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	return Reply.NativeReply;
}

bool UAGInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(GI))
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	const UAGInventorySlotDDO* DragDrop = Cast<UAGInventorySlotDDO>(InOperation);

	if (!IsValid(DragDrop))
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (DragDrop->WidgetRef->Item.GearType != EGearType::GT_None && Item.GearType != EGearType::GT_None)
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
		
	if (DragDrop->WidgetRef->Item.GearType != EGearType::GT_None && Item.GearType == EGearType::GT_None)
	{
		if (DragDrop->WidgetRef->Item.GearType == EGearType::GT_Weapon)
		{
			if (Item.bIsEmpty || Item.LootClass->IsChildOf(AAGDLootGearWeapon::StaticClass()))
				GI->UnEquipToInventory(EGearType::GT_Weapon, InventoryIndex);
		}
		
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	}

	if (Item.GearType == EGearType::GT_None)
		GI->SwapInventoryItems(DragDrop->WidgetRef->InventoryIndex, InventoryIndex);
	else
	{
		if (DragDrop->WidgetRef->Item.LootClass->IsChildOf(AAGDLootGearWeapon::StaticClass()) && Item.GearType == EGearType::GT_Weapon)
			GI->ActivateInventoryItem(DragDrop->WidgetRef->InventoryIndex);
	}
	
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UAGInventorySlotWidget::EnableHighlight(bool Enable)
{
	if (Enable && !Item.bIsEmpty)
	{
		IMG_Highlight->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		return;
	}

	IMG_Highlight->SetVisibility(ESlateVisibility::Hidden);
}

void UAGInventorySlotWidget::EnableItemInfoWidget(bool Enabled)
{
	if (Item.bIsEmpty || !IsValid(InventoryWidget))
		return;

	if (Enabled)
	{
		const FVector2D Position = GetCachedGeometry().GetAbsolutePositionAtCoordinates(FVector2D(0, 0));
		
		InventoryWidget->EnableItemInfoWidget(Item, Position);

		return;
	}

	InventoryWidget->EnableItemInfoWidget(FInventoryItem(), FVector2D());
}

void UAGInventorySlotWidget::UpdateSlot(const bool& bForceEmpty)
{
	if (Item.bIsEmpty || bForceEmpty)
	{
		IMG_Border->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		IMG_Icon->SetBrushFromTexture(nullptr);
		IMG_Icon->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	IMG_Border->SetColorAndOpacity(NormalTint);
	IMG_Icon->SetBrushFromTexture(Item.LootClass.GetDefaultObject()->Icon);
	IMG_Icon->SetVisibility(ESlateVisibility::Visible);
	
	if (!HasAnyUserFocus() && !IsHovered())
		return;

	EnableHighlight(true);
}
