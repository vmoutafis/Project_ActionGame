// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGames/AGSaveGame.h"

bool UAGSaveGame::AddItemToInventory(const FInventoryItem& Item)
{
	for (int i = 0; i < PlayerInventory.Num(); ++i)
	{
		if (PlayerInventory[i].bIsEmpty)
		{
			PlayerInventory[i] = FInventoryItem(Item.LootClass, Item.Rarity);
			UE_LOG(LogTemp, Warning, TEXT("Item successfully added to inventory at slot: %i"), i)
			return true;
		}

		if (i == PlayerInventory.Num() -1)
			UE_LOG(LogTemp, Warning, TEXT("No free inventory slots."))
	}

	return false;
}
