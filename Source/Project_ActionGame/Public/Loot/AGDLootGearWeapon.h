// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGLootGear.h"
#include "AGDLootGearWeapon.generated.h"

class AAGWeapon;

UCLASS()
class PROJECT_ACTIONGAME_API AAGDLootGearWeapon : public AAGLootGear
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAGDLootGearWeapon();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<AAGWeapon> WeaponClass;
	
};
