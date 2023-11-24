// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot/AGDLootGearWeapon.h"


// Sets default values
AAGDLootGearWeapon::AAGDLootGearWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 1.0f;
	DamageType = UDamageType::StaticClass();
}

