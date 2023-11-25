// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGGameMenuBtnWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

UAGGameMenuBtnWidget::UAGGameMenuBtnWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BTN_MainButton = nullptr;
	TXT_MainButtonText = nullptr;
	ButtonText = FString("Button Text");
}

void UAGGameMenuBtnWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(TXT_MainButtonText))
		TXT_MainButtonText->SetText(FText::FromString(ButtonText));

	if (IsValid(BTN_MainButton))
	{
		BTN_MainButton->OnPressed.AddUniqueDynamic(this, &UAGGameMenuBtnWidget::OnPressed);
		BTN_MainButton->OnReleased.AddUniqueDynamic(this, &UAGGameMenuBtnWidget::OnReleased);
		BTN_MainButton->OnHovered.AddUniqueDynamic(this, &UAGGameMenuBtnWidget::OnHovered);
		BTN_MainButton->OnUnhovered.AddUniqueDynamic(this, &UAGGameMenuBtnWidget::OnUnHovered);
	}
}

void UAGGameMenuBtnWidget::OnPressed()
{
	Delegate_OnPressed.Broadcast();
}

void UAGGameMenuBtnWidget::OnReleased()
{
	Delegate_OnReleased.Broadcast();
}

void UAGGameMenuBtnWidget::OnHovered()
{
	Delegate_OnHovered.Broadcast();
}

void UAGGameMenuBtnWidget::OnUnHovered()
{
	Delegate_OnUnHovered.Broadcast();
}
