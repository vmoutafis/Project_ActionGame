// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemInfoWidget.h"

#include "AGHelperFunctions.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Loot/AGDLootGearWeapon.h"
#include "Loot/AGLoot.h"
#include "UserWidgets/AGItemInfoIconTextWidget.h"
#include "UserWidgets/AGItemInfoTextWidget.h"
#include "Weapons/AGWeapon.h"

UAGItemInfoWidget::UAGItemInfoWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemInfoTextClass = nullptr;
	ItemInfoIconClass = nullptr;
	IMG_Border = nullptr;
	TXT_Rarity = nullptr;
	TXT_Value = nullptr;
	TXT_DisplayName = nullptr;
	VB_ItemInfo = nullptr;
	FireIcon = FElementIcon();
	FrostIcon = FElementIcon();
	BaseDamageIcon = FElementIcon();
}

void UAGItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	VB_ItemInfo->ClearChildren();
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

	if (!IsValid(ItemInfoTextClass) || !IsValid(ItemInfoIconClass))
		return;
	
	if (const AAGDLootGearWeapon* WeaponLoot = Cast<AAGDLootGearWeapon>(Item.LootClass.GetDefaultObject()))
	{
		UAGItemInfoIconTextWidget* DamageText = CreateWidget<UAGItemInfoIconTextWidget>(GetOwningPlayer(), ItemInfoIconClass);
		const float DamageValue = WeaponLoot->WeaponClass.GetDefaultObject()->GetFullWeaponDamageCustomRarity(Item.Rarity);
		
		if (IsValid(DamageText))
		{
			DamageText->SetIcon(BaseDamageIcon.Icon, BaseDamageIcon.Colour);
			DamageText->TXT_Text->SetText(FText::FromString(FString::FromInt(FMath::TruncToInt(DamageValue))));
			VB_ItemInfo->AddChild(DamageText);
			DamageText->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 5.0f));
		}

		TArray<TEnumAsByte<ESpecialDamageTypes>> ElementTypes = UAGHelperFunctions::GetSpecialDamageTypesAsArray();

		for (const TEnumAsByte<ESpecialDamageTypes> Type : ElementTypes)
		{
			const float EleDamageValue = WeaponLoot->WeaponClass.GetDefaultObject()->GetElementalDamageCustomRarity(Type, Item.Rarity);

			if (EleDamageValue <= 0.0f)
				continue;
			
			UAGItemInfoIconTextWidget* EleDamageText = CreateWidget<UAGItemInfoIconTextWidget>(GetOwningPlayer(), ItemInfoIconClass);

			if (IsValid(EleDamageText))
			{
				EleDamageText->SetIcon(GetItemInfoElementIcon(Type).Icon, GetItemInfoElementIcon(Type).Colour);
				EleDamageText->TXT_Text->SetText(FText::FromString(FString::FromInt(FMath::TruncToInt(EleDamageValue))));
				VB_ItemInfo->AddChild(EleDamageText);
				EleDamageText->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 5.0f));
			}
		}
	}
}

FElementIcon UAGItemInfoWidget::GetItemInfoElementIcon(TEnumAsByte<ESpecialDamageTypes> Type)
{
	switch (Type)
	{
	case SDT_Fire:
		return FireIcon;
	case SDT_Frost:
		return FrostIcon;
	default:
		break;
	}

	return FElementIcon();
}
