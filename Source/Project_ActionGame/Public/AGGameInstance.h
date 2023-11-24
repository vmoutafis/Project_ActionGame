// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Engine/GameInstance.h"
#include "AGGameInstance.generated.h"

class UAGSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemAddedToInventory, FInventoryItem, Item);

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UAGGameInstance();

	bool AddInventoryItem(FInventoryItem Item);

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FItemAddedToInventory Delegate_OnItemAddedToInventory;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Save|Game")
	UAGSaveGame* SaveGame;

	UPROPERTY(EditDefaultsOnly, Category="Save|Game")
	FString SaveGameSlotName;
	
};
