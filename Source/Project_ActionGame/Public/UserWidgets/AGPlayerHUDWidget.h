// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGPlayerHUDWidget.generated.h"

struct FOnAttributeChangeData;
class UAGPlayerHealthWidget;
class UScrollBox;
class UAGItemCollectWidget;
struct FInventoryItem;
class UAGAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void CollectItem(FInventoryItem Item);

	UAGPlayerHealthWidget* GetPlayerHealthWidget() const { return PHW_PlayerHealth; }
	
protected:
	UFUNCTION()
	void AddItemToCollected();
	
	UFUNCTION()
	void RemoveCollectedItem();

	UFUNCTION()
	void ScrollNextCollectedItem();

	UFUNCTION()
	void UpdateHealth(float Current, float Max);

	UFUNCTION()
	void UpdateShield(float Current, float Max);

	UFUNCTION()
	void UpdateLevel(float Current, float Max);

	UFUNCTION()
	void UpdateExperience(float Current, float Max);

	void UpdateHealthWidget();

	void InitialiseHealthWidget();

	UFUNCTION()
	void InitialiseAbilitySystem();

	void OnAbilitySystemInit();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category=ItemCollect)
	TSubclassOf<UAGItemCollectWidget> ItemCollectWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=ItemCollect, meta=(BindWidget))
	UScrollBox* SB_ItemCollect;

	TArray<FInventoryItem> CollectedItems;

	bool TempCollectItemsSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerHealth", meta=(BindWidget))
	UAGPlayerHealthWidget* PHW_PlayerHealth;

	UPROPERTY()
	UAGAbilitySystemComponent* AbilitySystemComponent;

	FTimerHandle TH_RemoveCollectedItem;
	FTimerHandle TH_ScrollNextCollectedItem;
	FTimerHandle TH_AddItemToCollected;
	FTimerHandle TH_InitHealthWidget;
};
