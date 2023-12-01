// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemInfoTextWidget.h"

#include "Components/TextBlock.h"

void UAGItemInfoTextWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!IsValid(TXT_Text))
		return;

	TXT_Text->SetText(FText::FromString("Damage: +1"));
}
