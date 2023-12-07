// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemInfoWidget.h"

#include "AGHelperFunctions.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Loot/AGDLootGearWeapon.h"
#include "Loot/AGLoot.h"
#include "UserWidgets/AGItemInfoTextWidget.h"
#include "Weapons/AGWeapon.h"

UAGItemInfoWidget::UAGItemInfoWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemInfoClass = UAGItemInfoTextWidget::StaticClass();
	IMG_Border = nullptr;
	TXT_Rarity = nullptr;
	TXT_Value = nullptr;
	TXT_DisplayName = nullptr;
	VB_ItemInfo = nullptr;
}

void UAGItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UAGItemInfoWidget::SetItem(const FInventoryItem& NewItem)
{
	if (NewItem.bIsEmpty)
		return;
	
	Item = NewItem;
	IMG_Border->SetColorAndOpacity(UAGHelperFunctions::GetRarityColour(Item.Rarity));
	
	TXT_DisplayName->SetText(FText::FromString(Item.LootClass.GetDefaultObject()->DisplayName));
	
	TXT_Rarity->SetText(FText::FromString(UAGHelperFunctions::GetRarityAsString(Item.Rarity)));
	TXT_Rarity->SetColorAndOpacity(UAGHelperFunctions::GetRarityColour(Item.Rarity));

	const int Value = Item.LootClass.GetDefaultObject()->CostValue * UAGHelperFunctions::GetRarityMultiplier(Item.Rarity);
	TXT_Value->SetText(FText::FromString(FString::FromInt(Value)));

	VB_ItemInfo->ClearChildren();

	if (!IsValid(ItemInfoClass))
		return;
	
	if (const AAGDLootGearWeapon* WeaponLoot = Cast<AAGDLootGearWeapon>(Item.LootClass.GetDefaultObject()))
	{
		UAGItemInfoTextWidget* DamageText = CreateWidget<UAGItemInfoTextWidget>(GetOwningPlayer(), ItemInfoClass);
		const float DamageValue = WeaponLoot->WeaponClass.GetDefaultObject()->GetRarityDamage(Item.Rarity);
		DamageText->TXT_Text->SetText(FText::FromString(FString("Damage: +") + FString::FromInt(static_cast<int>(DamageValue))));
		VB_ItemInfo->AddChild(DamageText);
	}
}

void UAGItemInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D ViewportSize;
	const FVector2D WidgetSize = GetPaintSpaceGeometry().GetAbsoluteSize();
	const FVector2D ViewportPos = GetPaintSpaceGeometry().GetAbsolutePosition();

	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	
	if (ViewportPos.Y > ViewportSize.Y)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget: %f, ViewportY: %f"), ViewportPos.Y, ViewportSize.Y);
		
		FVector2D NewPosition = ViewportPos;
		NewPosition.Y = ViewportSize.Y - WidgetSize.Y;
		SetPositionInViewport(NewPosition, false);
	}
}
