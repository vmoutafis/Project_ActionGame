// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "GameFramework/SaveGame.h"
#include "AGSaveGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoInventorySpace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipmentUpdated, TEnumAsByte<EEquipmentSlots>, EquipSlot);

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UAGSaveGame();
	
	bool AddItemToInventory(const FInventoryItem& Item);

	FInventoryItem GetEquipmentItem(TEnumAsByte<EEquipmentSlots> Slot) const;

	void SetEquipmentItem(TEnumAsByte<EEquipmentSlots> Slot, const FInventoryItem& Item);

	bool ActivateInventoryItem(const int& Index, TEnumAsByte<EEquipmentSlots> Slot = ES_None);

	void SwapEquippedWeapons();

	void SwapInventoryItems(const int& ItemIndex1, const int& ItemIndex2);

	bool UnEquipToInventory(TEnumAsByte<EEquipmentSlots> Slot, const int& InventorySlot);

	UPROPERTY()
	FNoInventorySpace Delegate_NoInventorySpace;

	UPROPERTY()
	FEquipmentUpdated Delegate_EquipmentUpdated;
	
public:
	TArray<FInventoryItem> PlayerInventory;

	TArray<FInventoryItem> PlayerEquipment;
};
