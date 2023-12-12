// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGPlayerHealthWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UAGPlayerHealthWidget::UAGPlayerHealthWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PB_Health = nullptr;
	PB_Experience = nullptr;
	PB_Shield = nullptr;
	TXT_Level = nullptr;
}

void UAGPlayerHealthWidget::SetHealth(float Health, float MaxHealth)
{
	float ValuePercent = 0.0f;
	
	if (MaxHealth > 0)
		ValuePercent = Health / MaxHealth;
		
	PB_Health->SetPercent(ValuePercent);
}

void UAGPlayerHealthWidget::SetShield(float Shield, float MaxShield)
{
	float ValuePercent = 0.0f;
	
	if (MaxShield > 0)
		ValuePercent = Shield / MaxShield;
		
	PB_Shield->SetPercent(ValuePercent);
}

void UAGPlayerHealthWidget::SetExperience(float Experience, float MaxExperience)
{
	float ValuePercent = 0.0f;
	
	if (MaxExperience > 0)
		ValuePercent = Experience / MaxExperience;
		
	PB_Experience->SetPercent(ValuePercent);
}

void UAGPlayerHealthWidget::SetLevel(float Level)
{
	TXT_Level->SetText(FText::FromString(FString::FromInt(static_cast<int>(Level))));
}
