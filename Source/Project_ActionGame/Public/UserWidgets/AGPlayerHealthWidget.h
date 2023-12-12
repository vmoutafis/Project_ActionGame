// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGPlayerHealthWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGPlayerHealthWidget(const FObjectInitializer& ObjectInitializer);

	void SetHealth(float Health, float MaxHealth);

	void SetShield(float Shield, float MaxShield);

	void SetExperience(float Experience, float MaxExperience);

	void SetLevel(float Level);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UProgressBar* PB_Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UProgressBar* PB_Shield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UProgressBar* PB_Experience;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UTextBlock* TXT_Level;
};
