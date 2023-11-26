#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "AGDataTypes.generated.h"

class AAGLoot;

UENUM(BlueprintType)
enum EItemRarity : uint8
{
	IR_Common = 0 UMETA(DisplayName = "Common"),
	IR_UnCommon UMETA(DisplayName = "UnCommon"),
	IR_Rare UMETA(DisplayName = "Rare"),
	IR_Epic UMETA(DisplayName = "Epic"),
	IR_Legendary UMETA(DisplayName = "Legendary")
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	FInventoryItem()
	{
		bIsEmpty = true;
		LootClass = nullptr;
		Rarity = EItemRarity::IR_Common;
	}

	FInventoryItem(const FInventoryItem& Other)
	{
		bIsEmpty = Other.bIsEmpty;
		LootClass = Other.LootClass;
		Rarity = Other.Rarity;
	}

	FInventoryItem(TSubclassOf<AAGLoot> DefaultClass, TEnumAsByte<EItemRarity> DefaultRarity, bool IsEmpty = false)
	{
		bIsEmpty = IsEmpty;
		LootClass = DefaultClass;
		Rarity = DefaultRarity;
	}

	void Clear()
	{
		*this = FInventoryItem();
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsEmpty;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAGLoot> LootClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EItemRarity> Rarity;
};