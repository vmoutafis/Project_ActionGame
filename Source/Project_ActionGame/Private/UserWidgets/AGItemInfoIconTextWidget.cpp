// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemInfoIconTextWidget.h"

#include "Components/Image.h"

UAGItemInfoIconTextWidget::UAGItemInfoIconTextWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IMG_Icon = nullptr;
}

void UAGItemInfoIconTextWidget::SetIcon(UTexture2D* NewIcon, FLinearColor Colour)
{
	if (!IsValid(IMG_Icon) || !IsValid(NewIcon))
		return;

	IMG_Icon->SetBrushFromTexture(NewIcon);
	IMG_Icon->SetColorAndOpacity(Colour);
}
