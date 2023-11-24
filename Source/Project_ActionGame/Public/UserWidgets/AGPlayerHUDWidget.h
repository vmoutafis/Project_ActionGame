// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGPlayerHUDWidget.generated.h"

struct FInventoryItem;

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
protected:
	UFUNCTION()
	void OnItemAddedToInventory_Pure(FInventoryItem Item);

	UFUNCTION(BlueprintImplementableEvent, Category=Inventory)
	void OnItemAddedToInventory(const FInventoryItem& Item);
	
};
