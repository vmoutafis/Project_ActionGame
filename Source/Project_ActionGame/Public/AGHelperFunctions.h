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
	// This returns the special damage types out as an array (ignores None)
	static TArray<TEnumAsByte<ESpecialDamageTypes>> GetSpecialDamageTypesAsArray();
	
	static TEnumAsByte<EItemRarity> GetRandomRarity();

	static FLinearColor GetRarityColour(const TEnumAsByte<EItemRarity>& Rarity);

	static FString GetRarityAsString(const TEnumAsByte<EItemRarity>& Rarity);

	static float GetRarityMultiplier(const TEnumAsByte<EItemRarity>& Rarity);

	static void AGSimpleWarning(const FString& Message);

	static void AGSimpleError(const FString& Message);

	static void AGObjectWarning(const UObject* Object, const FString& Message);

	static void AGObjectError(const UObject* Object,const FString& Message);
};
