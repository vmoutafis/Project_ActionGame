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

UENUM(BlueprintType)
enum EGearType: uint8
{
	GT_Head = 0 UMETA(DisplayName = "Head"),
	GT_Neck UMETA(DisplayName = "Neck"),
	GT_UpperBody UMETA(DisplayName = "Upper Body"),
	GT_Hands UMETA(DisplayName = "Hands"),
	GT_Ring UMETA(DisplayName = "Ring"),
	GT_Legs UMETA(DisplayName = "Legs"),
	GT_Feet UMETA(DisplayName = "Feet"),
	GT_Weapon UMETA(DisplayName = "Weapon"),
	GT_None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum EEquipmentSlots: uint8
{
	ES_Head = 0 UMETA(DisplayName = "Head"),
	ES_Neck UMETA(DisplayName = "Neck"),
	ES_UpperBody UMETA(DisplayName = "Upper Body"),
	ES_Hands UMETA(DisplayName = "Hands"),
	ES_Ring UMETA(DisplayName = "Ring"),
	ES_Legs UMETA(DisplayName = "Legs"),
	ES_Feet UMETA(DisplayName = "Feet"),
	ES_Weapon UMETA(DisplayName = "Weapon"),
	ES_SecondaryWeapon UMETA(DisplayName = "Secondary Weapon"),
	ES_None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum ESpecialDamageTypes: uint8
{
	SDT_None = 0 UMETA(DisplayName = "None"),
	SDT_Fire UMETA(DisplayName = "Fire"),
	SDT_Frost UMETA(DisplayName = "Frost")
};

UENUM(BlueprintType)
enum EWeaponTypes: uint8
{
	WT_None = 0 UMETA(DisplayName = "None"),
	WT_Sword UMETA(DisplayName = "Sword"),
	WT_Rifle UMETA(DisplayName = "Rifle"),
	WT_Pistol UMETA(DisplayName = "Pistol")
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
		GearType = EGearType::GT_None;
	}

	FInventoryItem(const FInventoryItem& Other)
	{
		bIsEmpty = Other.bIsEmpty;
		LootClass = Other.LootClass;
		Rarity = Other.Rarity;
		GearType = Other.GearType;
	}

	FInventoryItem(TSubclassOf<AAGLoot> DefaultClass, TEnumAsByte<EItemRarity> DefaultRarity,
		bool IsEmpty = false, TEnumAsByte<EGearType> DefaultGearType = EGearType::GT_None)
	{
		bIsEmpty = IsEmpty;
		LootClass = DefaultClass;
		Rarity = DefaultRarity;
		GearType = DefaultGearType;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EGearType> GearType;
};