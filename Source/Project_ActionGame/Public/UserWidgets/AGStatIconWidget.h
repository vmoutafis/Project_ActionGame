// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGStatIconWidget.generated.h"

class UImage;
class UTextBlock;
class UTexture2D;

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGStatIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGStatIconWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;
	
	void SetValue(const float& Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stat)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stat)
	FLinearColor IconColour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stat)
	float DebugValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Stat, meta=(BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Stat, meta=(BindWidget))
	UTextBlock* TXT_Value;
};
