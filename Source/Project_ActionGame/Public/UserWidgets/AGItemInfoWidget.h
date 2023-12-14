// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "AGItemInfoWidget.generated.h"

class UAGItemInfoIconTextWidget;
class UAGItemInfoTextWidget;
class UVerticalBox;
class UTextBlock;
class UImage;
struct FInventoryItem;

USTRUCT(BlueprintType)
struct FElementIcon
{
	GENERATED_BODY()

	FElementIcon()
	{
		Icon = nullptr;
		Colour = FLinearColor(1.0f, 1.0f, 1.0f);
	}

	FElementIcon(UTexture2D* SetIcon, const FLinearColor& SetColour)
	{
		Icon = SetIcon;
		Colour = SetColour;
	}
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere)
	FLinearColor Colour;
};

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

	FElementIcon GetItemInfoElementIcon(TEnumAsByte<ESpecialDamageTypes> Type);

protected:
	FInventoryItem Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item)
	TSubclassOf<UAGItemInfoTextWidget> ItemInfoTextClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Item)
	TSubclassOf<UAGItemInfoIconTextWidget> ItemInfoIconClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Damage Icons")
	FElementIcon BaseDamageIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Damage Icons")
	FElementIcon FireIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Damage Icons")
	FElementIcon FrostIcon;
	
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
