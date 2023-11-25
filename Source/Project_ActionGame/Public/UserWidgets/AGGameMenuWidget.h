// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGGameMenuWidget.generated.h"

class UAGInventoryWidget;
class UCanvasPanel;
class UAGGameMenuNavWidget;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGGameMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="GameMenu", meta=(BindWidget))
	UCanvasPanel* CP_GameMenu;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="GameMenu", meta=(BindWidget))
	UWidgetSwitcher* WS_MenuWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="GameMenu", meta=(BindWidget))
	UAGGameMenuNavWidget* GMN_Navigation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="GameMenu|Inventory", meta=(BindWidget))
	UAGInventoryWidget* INV_InventoryMenu;
};
