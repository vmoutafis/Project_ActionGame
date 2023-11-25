// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGGameMenuNavWidget.generated.h"

class UAGGameMenuBtnWidget;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGGameMenuNavWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGGameMenuNavWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=GameMenuButton, meta=(BindWidget))
	UAGGameMenuBtnWidget* BTN_Inventory;
	
};
