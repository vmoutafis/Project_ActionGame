// Fill out your copyright notice in the Description page of Project Settings.


#include "AGHelperFunctions.h"

#include "Kismet/KismetMathLibrary.h"

TArray<TEnumAsByte<ESpecialDamageTypes>> UAGHelperFunctions::GetSpecialDamageTypesAsArray()
{
	return TArray<TEnumAsByte<ESpecialDamageTypes>>({ SDT_Fire, SDT_Frost });
}

TEnumAsByte<EItemRarity> UAGHelperFunctions::GetRandomRarity()
{
	if (UKismetMathLibrary::RandomBoolWithWeight(0.1f))
		return EItemRarity::IR_Legendary;

	if (UKismetMathLibrary::RandomBoolWithWeight(0.2))
		return EItemRarity::IR_Epic;

	if (UKismetMathLibrary::RandomBoolWithWeight(0.3))
		return EItemRarity::IR_Rare;

	if (UKismetMathLibrary::RandomBoolWithWeight(0.5))
		return EItemRarity::IR_UnCommon;

	return EItemRarity::IR_Common;
}

FLinearColor UAGHelperFunctions::GetRarityColour(const TEnumAsByte<EItemRarity>& Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::IR_Common :
		return FLinearColor(1.0f, 1.0f, 1.0f);
	case EItemRarity::IR_UnCommon :
		return FLinearColor(0, 1.0f, 0);
	case EItemRarity::IR_Rare :
		return FLinearColor(0, 0.5f, 1.0f);
	case EItemRarity::IR_Epic :
		return FLinearColor(1.0f, 0, 1.0f);
	case EItemRarity::IR_Legendary :
		return FLinearColor(1.0f, 0.25f, 0);
		default:
			return FLinearColor(1.0f, 0, 0);
	}
}

FString UAGHelperFunctions::GetRarityAsString(const TEnumAsByte<EItemRarity>& Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::IR_Common :
		return FString("Common");
	case EItemRarity::IR_UnCommon :
		return FString("UnCommon");
	case EItemRarity::IR_Rare :
		return FString("Rare");
	case EItemRarity::IR_Epic :
		return FString("Epic");
	case EItemRarity::IR_Legendary :
		return FString("Legendary");
	default:
		return FString("Common");
	}
}

float UAGHelperFunctions::GetRarityMultiplier(const TEnumAsByte<EItemRarity>& Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::IR_Common :
		return 1.0f;
	case EItemRarity::IR_UnCommon :
		return 2.0f;
	case EItemRarity::IR_Rare :
		return 3.0f;
	case EItemRarity::IR_Epic :
		return 4.0f;
	case EItemRarity::IR_Legendary :
		return 6.0f;
	default:
		return 1.0f;
	}
}

void UAGHelperFunctions::AGSimpleWarning(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message)
}

void UAGHelperFunctions::AGSimpleError(const FString& Message)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *Message)
}

void UAGHelperFunctions::AGObjectWarning(const UObject* Object, const FString& Message)
{
	AGSimpleWarning(FString(Object->GetName()) + ": " + Message);
}

void UAGHelperFunctions::AGObjectError(const UObject* Object, const FString& Message)
{
	AGSimpleError(FString(Object->GetName()) + ": " + Message);
}

TEnumAsByte<EGearType> UAGHelperFunctions::ConvertEquipSlotToGearType(TEnumAsByte<EEquipmentSlots> Slot)
{
	TEnumAsByte<EGearType> ConvertedType = GT_None;
	
	switch (Slot)
	{
		case ES_Head :
			ConvertedType = GT_Head;
			break;
		case ES_UpperBody :
			ConvertedType = GT_UpperBody;
			break;
		case ES_Neck :
			ConvertedType = GT_Neck;
			break;
		case ES_Hands :
			ConvertedType = GT_Hands;
			break;
		case ES_Ring :
			ConvertedType = GT_Ring;
			break;
		case ES_Legs :
			ConvertedType = GT_Legs;
			break;
		case ES_Feet :
			ConvertedType = GT_Feet;
			break;
		case ES_Weapon :
			ConvertedType = GT_Weapon;
			break;
		case ES_SecondaryWeapon :
			ConvertedType = GT_Weapon;
			break;
		default: break;
	}

	return ConvertedType;
}
