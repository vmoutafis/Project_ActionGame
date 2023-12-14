// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGItemInfoTextWidget.generated.h"

UENUM(BlueprintType)
enum EGearStatArrows
{
	GSA_Up = 0 UMETA(DisplayName = "Up"),
	GSA_Down UMETA(DisplayName = "Down"),
	GSA_Middle UMETA(DisplayName = "Middle")
};

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGItemInfoTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGItemInfoTextWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativePreConstruct() override;

	void SetArrow(TEnumAsByte<EGearStatArrows> Direction);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Text, meta=(BindWidget))
	UTextBlock* TXT_Text;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Arrow, meta=(BindWidget))
	UImage* IMG_Arrow;

	UPROPERTY(EditDefaultsOnly, Category=Arrow)
	UTexture2D* UpArrow;

	UPROPERTY(EditDefaultsOnly, Category=Arrow)
    UTexture2D* DownArrow;

	UPROPERTY(EditDefaultsOnly, Category=Arrow)
	UTexture2D* MidArrow;
};
