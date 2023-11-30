// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGames/AGSaveGame.h"

#include "AGHelperFunctions.h"
#include "Loot/AGDLootGearWeapon.h"

UAGSaveGame::UAGSaveGame()
{
	PlayerEquipment.SetNum(8);

	PlayerEquipment[EGearType::GT_Head].GearType = EGearType::GT_Head;
	PlayerEquipment[EGearType::GT_Neck].GearType = EGearType::GT_Neck;
	PlayerEquipment[EGearType::GT_UpperBody].GearType = EGearType::GT_UpperBody;
	PlayerEquipment[EGearType::GT_Hands].GearType = EGearType::GT_Hands;
	PlayerEquipment[EGearType::GT_Ring].GearType = EGearType::GT_Ring;
	PlayerEquipment[EGearType::GT_Legs].GearType = EGearType::GT_Legs;
	PlayerEquipment[EGearType::GT_Feet].GearType = EGearType::GT_Feet;
	PlayerEquipment[EGearType::GT_Weapon].GearType = EGearType::GT_Weapon;
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
	PlayerEquipment[GearType].GearType = GearType;

	UAGHelperFunctions::AGSimpleWarning("Equipment Item Set.");
	Delegate_EquipmentUpdated.Broadcast(GearType);
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
		PlayerInventory[Index].GearType = EGearType::GT_None;
	}

	return true;
}

void UAGSaveGame::SwapInventoryItems(const int& ItemIndex1, const int& ItemIndex2)
{
	if (ItemIndex1 == -1 || ItemIndex2 == -1)
		return;

	if (!PlayerInventory.IsValidIndex(ItemIndex1) || !PlayerInventory.IsValidIndex(ItemIndex2))
		return;

	const FInventoryItem Item1Ref = PlayerInventory[ItemIndex1];

	PlayerInventory[ItemIndex1] = PlayerInventory[ItemIndex2];
	PlayerInventory[ItemIndex2] = Item1Ref;
}

bool UAGSaveGame::UnEquipToInventory(TEnumAsByte<EGearType> GearTypeSlot, const int& InventorySlot)
{
	if (!PlayerInventory.IsValidIndex(InventorySlot))
		return false;

	const FInventoryItem InventoryItem = PlayerInventory[InventorySlot];
	
	PlayerInventory[InventorySlot] = PlayerEquipment[GearTypeSlot];
	PlayerInventory[InventorySlot].GearType = EGearType::GT_None;

	SetEquipmentItem(GearTypeSlot, InventoryItem);
	
	return true;
}
