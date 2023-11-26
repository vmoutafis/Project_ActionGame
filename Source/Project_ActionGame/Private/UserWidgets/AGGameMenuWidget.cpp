// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets\AGGameMenuWidget.h"

#include "AGPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Components/WidgetSwitcher.h"

UAGGameMenuWidget::UAGGameMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CP_GameMenu = nullptr;
	GMN_Navigation = nullptr;
	WS_MenuWidgets = nullptr;
	INV_InventoryMenu = nullptr;
	SetIsFocusable(true);
}

FReply UAGGameMenuWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetDisplayName().EqualTo(FText::FromString(FString("Tab"))))
		Cast<AAGPlayerController>(GetOwningPlayer())->ToggleGameMenu();
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}
