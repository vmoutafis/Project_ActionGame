// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "AGItemInfoWidget.generated.h"

class UImage;
struct FInventoryItem;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGItemInfoWidget();

	virtual void NativeConstruct() override;
	
	void SetItem(const FInventoryItem& NewItem);

protected:
	FInventoryItem Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item)
	UImage* IMG_Border;
	
};
