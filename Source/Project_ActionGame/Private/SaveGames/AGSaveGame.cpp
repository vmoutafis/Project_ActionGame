// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGames/AGSaveGame.h"

#include "Loot/AGDLootGearWeapon.h"

UAGSaveGame::UAGSaveGame()
{
	PlayerEquipment.SetNum(8);
}

bool UAGSaveGame::AddItemToInventory(const FInventoryItem& Item)
{
	for (int i = 0; i < PlayerInventory.Num(); ++i)
	{
		if (PlayerInventory[i].bIsEmpty)
		{
			PlayerInventory[i] = FInventoryItem(Item.LootClass, Item.Rarity);
			return true;
		}

		if (i >= PlayerInventory.Num() -1)
			Delegate_NoInventorySpace.Broadcast();
	}

	return false;
}

FInventoryItem UAGSaveGame::GetEquipmentItem(TEnumAsByte<EGearType> GearType) const
{
	return PlayerEquipment[GearType];
}

void UAGSaveGame::SetEquipmentItem(TEnumAsByte<EGearType> GearType, const FInventoryItem& Item)
{
	PlayerEquipment[GearType] = Item;
}

bool UAGSaveGame::ActivateInventoryItem(const int& Index)
{
	if (!PlayerInventory.IsValidIndex(Index))
		return false;

	if (PlayerInventory[Index].LootClass->IsChildOf(AAGDLootGearWeapon::StaticClass()))
	{
		const FInventoryItem CurrentItem = GetEquipmentItem(EGearType::GT_Weapon);
		
		SetEquipmentItem(EGearType::GT_Weapon, PlayerInventory[Index]);

		PlayerInventory[Index] = CurrentItem;
	}

	return true;
}
