// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AGDataTypes.h"
#include "AGHelperFunctions.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TEnumAsByte<EItemRarity> GetRandomRarity();

	static FLinearColor GetRarityColour(const TEnumAsByte<EItemRarity>& Rarity);
};
