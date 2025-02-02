﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Engine/GameInstance.h"
#include "AGGameInstance.generated.h"

class UAGSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLootColleced, FInventoryItem, Item);

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UAGGameInstance();

	bool CollectLoot(const FInventoryItem& Item);
	
	bool AddInventoryItem(const FInventoryItem& Item);

	void SwapInventoryItems(const int& ItemIndex1, const int& ItemIndex2);

	bool UnEquipToInventory(TEnumAsByte<EEquipmentSlots> EquipSlot, const int& InventorySlot);
	
	UPROPERTY()
	FInventoryUpdated Delegate_InventoryUpdated;

	UPROPERTY()
	FLootColleced Delegate_LootCollected;

	int GetNumInventoryItems();

	TArray<FInventoryItem> GetInventory();
	
	TArray<FInventoryItem> GetAllEquipment();
	
	FInventoryItem GetEquipmentBySlot(TEnumAsByte<EEquipmentSlots> Slot);

	bool ActivateInventoryItem(const int& Index, TEnumAsByte<EEquipmentSlots> Slot = ES_None);

	bool SwapEquippedWeapons();

protected:
	UAGSaveGame* CreateSaveGameObject(const bool& ForceNew = false);

	UFUNCTION()
	void EquipmentUpdated(TEnumAsByte<EEquipmentSlots> GearType);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	int MaxInventorySlots;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Save|Game")
	TSubclassOf<UAGSaveGame> SaveGameClass;
	
	UPROPERTY(BlueprintReadOnly, Category="Save|Game")
	UAGSaveGame* SaveGame;

	UPROPERTY(EditDefaultsOnly, Category="Save|Game")
	FString SaveGameSlotName;
	
};
