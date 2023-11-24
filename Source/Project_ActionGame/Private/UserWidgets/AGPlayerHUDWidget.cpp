// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGPlayerHUDWidget.h"

#include "..\..\Public\AGDataTypes.h"
#include "AGGameInstance.h"
#include "Loot/AGLoot.h"

void UAGPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(GI))
		return;

	GI->Delegate_OnItemAddedToInventory.AddDynamic(this, &UAGPlayerHUDWidget::OnItemAddedToInventory_Pure);
}

void UAGPlayerHUDWidget::OnItemAddedToInventory_Pure(FInventoryItem Item)
{
	OnItemAddedToInventory(std::move(Item));
	UE_LOG(LogTemp, Warning, TEXT("Item Added: %s"), *Item.LootClass->GetName());
}
