// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGPlayerHUDWidget.generated.h"

class UScrollBox;
class UAGItemCollectWidget;
struct FInventoryItem;

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

	void CollectItem(FInventoryItem Item);
	
protected:
	UFUNCTION()
	void AddItemToCollected();
	
	UFUNCTION()
	void RemoveCollectedItem();

	UFUNCTION()
	void ScrollNextCollectedItem();

protected:
	UPROPERTY(EditDefaultsOnly, Category=ItemCollect)
	TSubclassOf<UAGItemCollectWidget> ItemCollectWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=ItemCollect, meta=(BindWidget))
	UScrollBox* SB_ItemCollect;

	TArray<FInventoryItem> CollectedItems;
	
	FTimerHandle TH_RemoveCollectedItem;
	FTimerHandle TH_ScrollNextCollectedItem;
	FTimerHandle TH_AddItemToCollected;

	bool TempCollectItemsSet;
};
