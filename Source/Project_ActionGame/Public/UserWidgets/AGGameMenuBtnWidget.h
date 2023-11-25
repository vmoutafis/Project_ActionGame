// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGGameMenuBtnWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnHovered);

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGGameMenuBtnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGGameMenuBtnWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;

protected:
	void OnPressed();

	void OnReleased();

	void OnHovered();

	void OnUnHovered();
	
public:
	UPROPERTY(EditAnywhere, Category="GameMenuButton|Text")
	FString ButtonText;
	
	UPROPERTY(BlueprintAssignable, Category=GameMenuButton)
	FOnPressed Delegate_OnPressed;

	UPROPERTY(BlueprintAssignable, Category=GameMenuButton)
	FOnReleased Delegate_OnReleased;

	UPROPERTY(BlueprintAssignable, Category=GameMenuButton)
	FOnHovered Delegate_OnHovered;

	UPROPERTY(BlueprintAssignable, Category=GameMenuButton)
	FOnUnHovered Delegate_OnUnHovered;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=GameMenuButton, meta=(BindWidget))
	UButton* BTN_MainButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=GameMenuButton, meta=(BindWidget))
	UTextBlock* TXT_MainButtonText;
};
