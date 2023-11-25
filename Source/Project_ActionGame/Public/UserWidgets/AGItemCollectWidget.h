// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "AGItemCollectWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGItemCollectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGItemCollectWidget(const FObjectInitializer& ObjectInitializer);

	void InitialiseItem(FString NewDisplayName, UTexture2D* NewIcon, TEnumAsByte<EItemRarity> NewRarity);
	
	virtual void NativePreConstruct() override;

	float PlayDisappearAnim();

protected:
	void UpdateItemDetails() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item, meta=(ExposeOnSpawn=true))
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item, meta=(ExposeOnSpawn=true))
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item, meta=(ExposeOnSpawn=true))
	TEnumAsByte<EItemRarity> Rarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Item, meta=(BindWidget))
	UTextBlock* TXT_DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Item, meta=(BindWidget))
	UTextBlock* TXT_Rarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Item, meta=(BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Item, meta=(BindWidget))
	UImage* IMG_IconBG;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Animations, meta=(BindWidgetAnim))
	UWidgetAnimation* Anim_Disappear;
};
