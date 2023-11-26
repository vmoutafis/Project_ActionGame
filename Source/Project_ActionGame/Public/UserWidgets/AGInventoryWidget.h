// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGInventoryWidget.generated.h"

class UUniformGridPanel;
class UAGInventorySlotWidget;
class AAGLoot;
class UScrollBox;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGInventoryWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, Category=Inventory)
	TSubclassOf<UAGInventorySlotWidget> InventorySlotClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory|Debug")
	TSubclassOf<AAGLoot> DesignTimeLootClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory|Debug")
	int DebugInventoryMaxSlots;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UScrollBox* SB_Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UUniformGridPanel* UGP_Inventory;
};
