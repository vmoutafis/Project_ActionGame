// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGItemInfoTextWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGItemInfoTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Text, meta=(BindWidget))
	UTextBlock* TXT_Text;
};
