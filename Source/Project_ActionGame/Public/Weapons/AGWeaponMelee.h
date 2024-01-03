// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGWeapon.h"
#include "AGWeaponMelee.generated.h"

UCLASS()
class PROJECT_ACTIONGAME_API AAGWeaponMelee : public AAGWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAGWeaponMelee();

	TArray<UAnimMontage*> GetAirAttackAnims() const { return AirAttackAnims; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Melee Weapon|Animations")
	TArray<UAnimMontage*> AirAttackAnims;
};
