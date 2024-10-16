// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loot/AGLoot.h"
#include "AGLootGear.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAGLootGear : public AAGLoot
{
	GENERATED_BODY()

public:
	AAGLootGear();
	
	virtual void BeginPlay() override;

	virtual void Collect(TEnumAsByte<EGearType> GearType = GT_None) override;

public:
	UPROPERTY(EditDefaultsOnly, Category=Gear)
	TEnumAsByte<EGearType> Type;
	
};
