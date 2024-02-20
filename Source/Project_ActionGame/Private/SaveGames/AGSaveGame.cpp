// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGames/AGSaveGame.h"

#include "AGHelperFunctions.h"
#include "Loot/AGDLootGearWeapon.h"

UAGSaveGame::UAGSaveGame()
{
	PlayerEquipment.SetNum(9);

	PlayerEquipment[ES_Hands].GearType = GT_Head;
	PlayerEquipment[ES_Neck].GearType = GT_Neck;
	PlayerEquipment[ES_UpperBody].GearType = GT_UpperBody;
	PlayerEquipment[ES_Hands].GearType = GT_Hands;
	PlayerEquipment[ES_Ring].GearType = GT_Ring;
	PlayerEquipment[ES_Legs].GearType = GT_Legs;
	PlayerEquipment[ES_Feet].GearType = GT_Feet;
	PlayerEquipment[ES_Weapon].GearType = GT_Weapon;
	PlayerEquipment[ES_SecondaryWeapon].GearType = GT_Weapon;
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

FInventoryItem UAGSaveGame::GetEquipmentItem(TEnumAsByte<EEquipmentSlots> Slot) const
{
	return PlayerEquipment[Slot];
}

void UAGSaveGame::SetEquipmentItem(TEnumAsByte<EEquipmentSlots> GearType, const FInventoryItem& Item)
{
	PlayerEquipment[GearType] = Item;
	PlayerEquipment[GearType].GearType = Item.GearType;

	Delegate_EquipmentUpdated.Broadcast(Item.GearType);
}

bool UAGSaveGame::ActivateInventoryItem(const int& Index, TEnumAsByte<EEquipmentSlots> Slot)
{
	if (!PlayerInventory.IsValidIndex(Index))
		return false;

	if (PlayerInventory[Index].LootClass->IsChildOf(AAGDLootGearWeapon::StaticClass()))
	{
		if (Slot == ES_None)
		{
			const bool bPrimaryEquipped = !GetEquipmentItem(ES_Weapon).bIsEmpty;
			Slot = ES_Weapon;
		
			if (bPrimaryEquipped)
				Slot = ES_SecondaryWeapon;
		}

		const FInventoryItem CurrentItem = GetEquipmentItem(Slot);
			
		SetEquipmentItem(Slot, PlayerInventory[Index]);

		PlayerInventory[Index] = CurrentItem;
		PlayerInventory[Index].GearType = GT_None;
	}

	return true;
}

void UAGSaveGame::SwapEquippedWeapons()
{
	const FInventoryItem OldPrimary = PlayerEquipment[ES_Weapon];

	PlayerEquipment[ES_Weapon] = PlayerEquipment[ES_SecondaryWeapon];
	PlayerEquipment[ES_SecondaryWeapon] = OldPrimary;
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

bool UAGSaveGame::UnEquipToInventory(TEnumAsByte<EEquipmentSlots> EquipmentSlot, const int& InventorySlot)
{
	if (!PlayerInventory.IsValidIndex(InventorySlot))
		return false;

	const FInventoryItem InventoryItem = PlayerInventory[InventorySlot];
	
	PlayerInventory[InventorySlot] = PlayerEquipment[EquipmentSlot];
	PlayerInventory[InventorySlot].GearType = GT_None;

	SetEquipmentItem(EquipmentSlot, InventoryItem);
	
	return true;
}
