// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGInventoryWidget.generated.h"

class UCanvasPanel;
struct FInventoryItem;
class UAGItemInfoWidget;
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

	virtual void NativeDestruct() override;

	void EnableItemInfoWidget(const FInventoryItem& Item, UAGInventorySlotWidget* SlotWidget);

protected:
	TArray<UAGInventorySlotWidget*> GetAllEquipmentSlots() const;

	UFUNCTION()
	void UpdateInventory();

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

	// Equipment slots
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Head;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Neck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_UpperBody;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Hands;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Ring;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Legs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Feet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGInventorySlotWidget* ISW_Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Inventory, meta=(BindWidget))
	UAGItemInfoWidget* IIW_ItemInfo;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Inventory)
	TSubclassOf<UAGItemInfoWidget> ItemInfoWidgetClass;
	
};
