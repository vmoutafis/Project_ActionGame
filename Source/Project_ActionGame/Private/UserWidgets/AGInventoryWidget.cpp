// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGInventoryWidget.h"

#include "AGDataTypes.h"
#include "AGGameInstance.h"
#include "AGHelperFunctions.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "UserWidgets/AGInventorySlotWidget.h"
#include "UserWidgets/AGItemInfoWidget.h"
#include "Weapons/AGWeapon.h"

UAGInventoryWidget::UAGInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SB_Inventory= nullptr;
	UGP_Inventory = nullptr;
	DesignTimeLootClass = AAGWeapon::StaticClass();
	InventorySlotClass = nullptr;
	DebugInventoryMaxSlots = 50;
	ISW_Head = nullptr;
	ISW_Neck = nullptr;
	ISW_UpperBody = nullptr;
	ISW_Hands = nullptr;
	ISW_Ring = nullptr;
	ISW_Legs = nullptr;
	ISW_Feet = nullptr;
	ISW_Weapon = nullptr;
	ItemInfoWidget = nullptr;
	ItemInfoWidgetClass = UAGItemInfoWidget::StaticClass();
}

void UAGInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!IsValid(UGP_Inventory) || !IsValid(InventorySlotClass))
		return;

	UGP_Inventory->ClearChildren();

	int Row = 0;
	int Column = 0;

	for (int i = 0; i < DebugInventoryMaxSlots; ++i)
	{
		UAGInventorySlotWidget* NewWidget = CreateWidget<UAGInventorySlotWidget>(GetWorld(), InventorySlotClass);
		
		if (i < 5 && IsDesignTime())
		{
			FInventoryItem Item = FInventoryItem(DesignTimeLootClass, UAGHelperFunctions::GetRandomRarity());
			NewWidget->SetSlot(this, &Item, i);
		}

		UGP_Inventory->AddChildToUniformGrid(NewWidget, Row, Column);

		if (Column > 2)
		{
			Column = 0;
			Row++;
		}
		else
			Column++;
	}
}

void UAGInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateInventory();

	Cast<UAGGameInstance>(GetGameInstance())->Delegate_InventoryUpdated.AddDynamic(this, &UAGInventoryWidget::UpdateInventory);

	ItemInfoWidget = CreateWidget<UAGItemInfoWidget>(GetOwningPlayer(), ItemInfoWidgetClass);
}

void UAGInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();

	Cast<UAGGameInstance>(GetGameInstance())->Delegate_InventoryUpdated.Clear();
}

void UAGInventoryWidget::EnableItemInfoWidget(const FInventoryItem& Item, FVector2D Position)
{
	if (Item.bIsEmpty)
	{
		ItemInfoWidget->SetVisibility(ESlateVisibility::Hidden);
		ItemInfoWidget->RemoveFromParent();
		return;
	}
	
	ItemInfoWidget->SetItem(Item);
	ItemInfoWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ItemInfoWidget->AddToViewport();
	ItemInfoWidget->ForceLayoutPrepass();
	
	FVector2D PixelPos;
	FVector2D ViewportPos;
	FVector2D ViewportSize;
	const FVector2D WidgetSize = ItemInfoWidget->GetDesiredSize();

	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), Position, PixelPos, ViewportPos);

	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	
	ViewportPos.Y = FMath::Min(ViewportPos.Y, ViewportSize.Y);
	ViewportPos.X = ViewportPos.X - WidgetSize.X;

	UE_LOG(LogTemp, Warning, TEXT("VSize: %f, WSize: %f, WPos: %f"), ViewportSize.Y, WidgetSize.Y, ViewportPos.Y)

	ItemInfoWidget->SetPositionInViewport(ViewportPos, false);

}

TArray<UAGInventorySlotWidget*> UAGInventoryWidget::GetAllEquipmentSlots() const
{
	return {
		ISW_Head,
		ISW_Neck,
		ISW_UpperBody,
		ISW_Hands,
		ISW_Ring,
		ISW_Legs,
		ISW_Feet,
		ISW_Weapon
	};
}

void UAGInventoryWidget::UpdateInventory()
{
	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(UGP_Inventory) || !IsValid(InventorySlotClass) || !IsValid(GI))
		return;
	
	UGP_Inventory->ClearChildren();
	
	int Row = 0;
	int Column = 0;
	
	for (int i = 0; i < GI->GetInventory().Num(); ++i)
	{
		UAGInventorySlotWidget* NewWidget = CreateWidget<UAGInventorySlotWidget>(GetWorld(), InventorySlotClass);

		NewWidget->SetSlot(this, &GI->GetInventory()[i], i);

		UGP_Inventory->AddChildToUniformGrid(NewWidget, Row, Column);

		if (Column > 2)
		{
			Column = 0;
			Row++;
		}
		else
			Column++;
	}

	for (int i = 0; i < GetAllEquipmentSlots().Num(); ++i)
	{
		GetAllEquipmentSlots()[i]->SetSlot(this, &GI->GetAllEquipment()[i], i);
		GetAllEquipmentSlots()[i]->SetAsEquipmentSlot(GI->GetAllEquipment()[i].GearType);
	}
}
