// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGStatWidget.h"

#include "Components/TextBlock.h"

UAGStatWidget::UAGStatWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TitleText = FString("Stat Name");
	DebugValue = 100.0f;
	TXT_Title = nullptr;
	TXT_Value = nullptr;
}

void UAGStatWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (IsValid(TXT_Title))
		TXT_Title->SetText(FText::FromString(TitleText));

	SetValue(DebugValue);
}

void UAGStatWidget::SetValue(const float& Value)
{
	if (!IsValid(TXT_Value))
		return;
	
	TXT_Value->SetText(FText::FromString(FString::FromInt(FMath::TruncToInt(Value))));
}
