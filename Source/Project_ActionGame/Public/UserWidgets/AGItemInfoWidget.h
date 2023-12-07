// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "AGItemInfoWidget.generated.h"

class UAGItemInfoTextWidget;
class UVerticalBox;
class UTextBlock;
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
	UAGItemInfoWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	
	void SetItem(const FInventoryItem& NewItem);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	FInventoryItem Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item)
	TSubclassOf<UAGItemInfoTextWidget> ItemInfoClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item, meta=(BindWidget))
	UImage* IMG_Border;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item, meta=(BindWidget))
	UTextBlock* TXT_DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item, meta=(BindWidget))
	UTextBlock* TXT_Rarity;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item, meta=(BindWidget))
	UVerticalBox* VB_ItemInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item, meta=(BindWidget))
	UTextBlock* TXT_Value;
	
};
