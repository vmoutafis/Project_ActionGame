﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AGGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGames/AGSaveGame.h"
#include "AGDataTypes.h"
#include "AGHelperFunctions.h"
#include "Characters/AGPlayerCharacter.h"

UAGGameInstance::UAGGameInstance()
{
	SaveGame = nullptr;
	MaxInventorySlots = 25;
}

bool UAGGameInstance::CollectLoot(const FInventoryItem& Item)
{
	const bool Result = AddInventoryItem(Item);

	if (Result)
		Delegate_LootCollected.Broadcast(Item);

	return Result;
}

bool UAGGameInstance::AddInventoryItem(const FInventoryItem& Item)
{
	if (GetInventory().Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No inventory exists."))
		return false;
	}

	const bool Result = SaveGame->AddItemToInventory(Item);

	if (Result)
		Delegate_InventoryUpdated.Broadcast();

	return Result;
}

void UAGGameInstance::SwapInventoryItems(const int& ItemIndex1, const int& ItemIndex2)
{
	if (!IsValid(CreateSaveGameObject()))
		return;

	SaveGame->SwapInventoryItems(ItemIndex1, ItemIndex2);

	Delegate_InventoryUpdated.Broadcast();
}

bool UAGGameInstance::UnEquipToInventory(TEnumAsByte<EGearType> GearTypeSlot, const int& InventorySlot)
{
	if (!IsValid(CreateSaveGameObject()))
		return false;

	const bool Result = SaveGame->UnEquipToInventory(GearTypeSlot, InventorySlot);

	if (Result)
		Delegate_InventoryUpdated.Broadcast();
	
	return Result;
}

int UAGGameInstance::GetNumInventoryItems()
{
	if (!IsValid(CreateSaveGameObject()))
		return 0;

	return SaveGame->PlayerInventory.Num();
}

TArray<FInventoryItem> UAGGameInstance::GetInventory()
{
	if (!CreateSaveGameObject())
		return TArray<FInventoryItem>();

	if (SaveGame->PlayerInventory.Num() != MaxInventorySlots)
		SaveGame->PlayerInventory.SetNum(MaxInventorySlots);
		
	return SaveGame->PlayerInventory;
}

TArray<FInventoryItem> UAGGameInstance::GetAllEquipment()
{
	if (!CreateSaveGameObject())
		return TArray<FInventoryItem>();
		
	return SaveGame->PlayerEquipment;
}

FInventoryItem UAGGameInstance::GetEquipmentByType(TEnumAsByte<EGearType> GearType)
{
	if (!CreateSaveGameObject())
		return FInventoryItem();
		
	return SaveGame->GetEquipmentItem(GearType);
}

bool UAGGameInstance::ActivateInventoryItem(const int& Index)
{
	if (!CreateSaveGameObject())
		return false;

	const bool Result = SaveGame->ActivateInventoryItem(Index);

	if (Result)
		Delegate_InventoryUpdated.Broadcast();
	
	return Result;
}

UAGSaveGame* UAGGameInstance::CreateSaveGameObject(const bool& ForceNew)
{
	if (IsValid(SaveGame) && !ForceNew)
		return SaveGame;
	
	SaveGame = Cast<UAGSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));

	SaveGame->Delegate_EquipmentUpdated.AddDynamic(this, &UAGGameInstance::EquipmentUpdated);
	
	return SaveGame;
}

void UAGGameInstance::EquipmentUpdated(TEnumAsByte<EGearType> GearType)
{
	if (AAGPlayerCharacter* PlayerRef = Cast<AAGPlayerCharacter>(GetPrimaryPlayerController()->GetPawn()))
	{
		if (GearType == EGearType::GT_Weapon)
		{
			const FInventoryItem Item = GetEquipmentByType(GearType);
			const FInventoryItem* ItemObj = nullptr;

			if (!Item.bIsEmpty)
				ItemObj = &Item;
			
			PlayerRef->EquipWeapon(ItemObj);
		}
	}
}
