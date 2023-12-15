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

	SetArrow(GSA_Up);

	if (!IsDesignTime())
		return;
	
	if (!IsValid(TXT_Text))
		return;

	if (TXT_Text->GetText().IsEmpty())
		TXT_Text->SetText(FText::FromString("Damage: +1"));
}

void UAGItemInfoTextWidget::SetArrow(TEnumAsByte<EGearStatArrows> Direction)
{
	IMG_Arrow->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	switch (Direction)
	{
	case GSA_Up:
		if (IsValid(UpArrow))
			IMG_Arrow->SetBrushFromMaterial(UpArrow);
		else
			IMG_Arrow->SetVisibility(ESlateVisibility::Hidden);
		break;
	case GSA_Down:
		if (IsValid(DownArrow))
			IMG_Arrow->SetBrushFromMaterial(DownArrow);
		else
			IMG_Arrow->SetVisibility(ESlateVisibility::Hidden);
		break;
	case GSA_Middle:
		if (IsValid(MidArrow))
			IMG_Arrow->SetBrushFromMaterial(MidArrow);
		else
			IMG_Arrow->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:
		break;
	}
}
