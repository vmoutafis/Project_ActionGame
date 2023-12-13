// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets\AGStatIconWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UAGStatIconWidget::UAGStatIconWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IMG_Icon = nullptr;
	DebugValue = 100.0f;
	Icon = nullptr;
	TXT_Value = nullptr;
	IconColour = FLinearColor(1.0f, 1.0f, 1.0f);
}

void UAGStatIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(IMG_Icon))
	{
		if (IsValid(Icon))
			IMG_Icon->SetBrushFromTexture(Icon);

		IMG_Icon->SetColorAndOpacity(IconColour);
	}
	
	SetValue(DebugValue);
}

void UAGStatIconWidget::SetValue(const float& Value)
{
	if (!IsValid(TXT_Value))
		return;
	
	TXT_Value->SetText(FText::FromString(FString::FromInt(FMath::TruncToInt(Value))));
}
