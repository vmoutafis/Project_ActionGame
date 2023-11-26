// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGStatWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGStatWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;

	void SetValue(const float& Value);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stat)
	FString TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stat)
	float DebugValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Stat, meta=(BindWidget))
	UTextBlock* TXT_Title;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Stat, meta=(BindWidget))
	UTextBlock* TXT_Value;
	
};
