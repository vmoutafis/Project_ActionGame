// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "GameFramework/SaveGame.h"
#include "AGSaveGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoInventorySpace);

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

	FInventoryItem GetEquipmentItem(TEnumAsByte<EGearType> GearType) const;

	void SetEquipmentItem(TEnumAsByte<EGearType> GearType, const FInventoryItem& Item);

	bool ActivateInventoryItem(const int& Index);
	
	FNoInventorySpace Delegate_NoInventorySpace;
	
public:
	TArray<FInventoryItem> PlayerInventory;

	TArray<FInventoryItem> PlayerEquipment;
};
