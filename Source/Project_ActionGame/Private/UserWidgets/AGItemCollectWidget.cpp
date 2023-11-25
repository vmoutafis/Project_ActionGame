// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemCollectWidget.h"

#include "AGHelperFunctions.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UAGItemCollectWidget::UAGItemCollectWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = FString("Item Name");
	Icon = nullptr;
	Rarity = EItemRarity::IR_Common;
	TXT_Rarity = nullptr;
	TXT_DisplayName = nullptr;
	IMG_Icon = nullptr;
	IMG_IconBG = nullptr;
	Anim_Disappear = nullptr;
}

void UAGItemCollectWidget::InitialiseItem(FString NewDisplayName, UTexture2D* NewIcon,
	TEnumAsByte<EItemRarity> NewRarity)
{
	DisplayName = NewDisplayName;

	if (IsValid(NewIcon))
		Icon = NewIcon;

	Rarity = NewRarity;

	UpdateItemDetails();
}

void UAGItemCollectWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateItemDetails();
}

float UAGItemCollectWidget::PlayDisappearAnim()
{
	if (!IsValid(Anim_Disappear))
		return 0.0f;
	
	PlayAnimation(Anim_Disappear, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, true);

	return Anim_Disappear->GetEndTime();
}

void UAGItemCollectWidget::UpdateItemDetails() const
{
	TXT_DisplayName->SetText(FText::FromString(DisplayName));

	TXT_Rarity->SetText(FText::FromString(UAGHelperFunctions::GetRarityAsString(Rarity)));

	IMG_Icon->SetBrushFromTexture(Icon);

	TXT_Rarity->SetColorAndOpacity(UAGHelperFunctions::GetRarityColour(Rarity));

	IMG_IconBG->SetColorAndOpacity(UAGHelperFunctions::GetRarityColour(Rarity));
}
