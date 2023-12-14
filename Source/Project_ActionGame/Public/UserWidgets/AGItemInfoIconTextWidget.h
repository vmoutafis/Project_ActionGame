// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/AGItemInfoTextWidget.h"
#include "AGItemInfoIconTextWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGItemInfoIconTextWidget : public UAGItemInfoTextWidget
{
	GENERATED_BODY()

public:
	UAGItemInfoIconTextWidget(const FObjectInitializer& ObjectInitializer);
	
	void SetIcon(UTexture2D* NewIcon, FLinearColor Colour = FLinearColor(1.0f, 1.0f, 1.0f));

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Text, meta=(BindWidget))
	UImage* IMG_Icon;
	
};
