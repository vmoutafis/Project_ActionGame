// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemInfoTextWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UAGItemInfoTextWidget::UAGItemInfoTextWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TXT_Text = nullptr;
	IMG_Arrow = nullptr;
	MidArrow = nullptr;
	UpArrow = nullptr;
	DownArrow = nullptr;
}

void UAGItemInfoTextWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!IsDesignTime())
		return;
	
	if (!IsValid(TXT_Text))
		return;

	if (TXT_Text->GetText().IsEmpty())
		TXT_Text->SetText(FText::FromString("Damage: +1"));
}

void UAGItemInfoTextWidget::SetArrow(TEnumAsByte<EGearStatArrows> Direction)
{
	IMG_Arrow->SetBrush()
}
