// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "GameFramework/SaveGame.h"
#include "AGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	bool AddItemToInventory(const FInventoryItem& Item);

public:
	TArray<FInventoryItem> PlayerInventory;

};
