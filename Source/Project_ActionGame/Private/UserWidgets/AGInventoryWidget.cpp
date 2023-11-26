// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGInventoryWidget.h"

#include "AGDataTypes.h"
#include "AGGameInstance.h"
#include "AGHelperFunctions.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "UserWidgets/AGInventorySlotWidget.h"
#include "Weapons/AGWeapon.h"

UAGInventoryWidget::UAGInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SB_Inventory= nullptr;
	UGP_Inventory = nullptr;
	DesignTimeLootClass = AAGWeapon::StaticClass();
	InventorySlotClass = nullptr;
	DebugInventoryMaxSlots = 50;
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
			NewWidget->SetSlot(&Item);
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

	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(UGP_Inventory) || !IsValid(InventorySlotClass) || !IsValid(GI))
		return;

	UGP_Inventory->ClearChildren();
	
	int Row = 0;
	int Column = 0;
	
	for (int i = 0; i < GI->GetInventory().Num(); ++i)
	{
		UAGInventorySlotWidget* NewWidget = CreateWidget<UAGInventorySlotWidget>(GetWorld(), InventorySlotClass);

		if (i < 5 && IsDesignTime())
		{
			FInventoryItem Item = FInventoryItem(DesignTimeLootClass, UAGHelperFunctions::GetRandomRarity());
			NewWidget->SetSlot(&Item);
		}
		else
			NewWidget->SetSlot(&GI->GetInventory()[i]);

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
