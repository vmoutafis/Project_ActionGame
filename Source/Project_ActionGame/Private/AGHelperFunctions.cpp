// Fill out your copyright notice in the Description page of Project Settings.


#include "AGHelperFunctions.h"

#include "Kismet/KismetMathLibrary.h"

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
		return FLinearColor(1.0f, 0.5f, 0);
		default:
			return FLinearColor(1.0f, 0, 0);
	}
}
