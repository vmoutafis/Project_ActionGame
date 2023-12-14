// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "GameFramework/Actor.h"
#include "AGWeapon.generated.h"

class UAGGameplayEffect;
class UBoxComponent;

UCLASS()
class PROJECT_ACTIONGAME_API AAGWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAGWeapon();

	void InitialiseWeapon(TEnumAsByte<EItemRarity> NewRarity, const float& AdditionalDamage = 0.0f);
	
	// Turn on the damage collider for the weapon
	void ActivateDamage();

	// Turn off the damage collider for the weapon
	void DeactivateDamage();

	float GetFullWeaponDamage() const;
	
	float GetFullWeaponDamageCustomRarity(const TEnumAsByte<EItemRarity>& CustomRarity) const;

	float GetElementalDamage(const TEnumAsByte<ESpecialDamageTypes> Type) const;

	float GetElementalDamageCustomRarity(const TEnumAsByte<ESpecialDamageTypes> Type, const TEnumAsByte<EItemRarity>& CustomRarity) const;

	float GetBaseDamage() const { return BaseDamage; }

	float GetRarityDamage(const TEnumAsByte<EItemRarity>& TestRarity) const;

	TSubclassOf<UAGGameplayEffect> GetWeaponStatsEffect() const { return WeaponStatsEffect; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDamageColliderHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	TSubclassOf<UAGGameplayEffect> WeaponStatsEffect;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	UBoxComponent* DamageCollision;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon|Damage")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, Category="Weapon|Damage")
	float FireDamage;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon|Damage")
	float FrostDamage;

	float SpecialDamage;

	UPROPERTY(EditDefaultsOnly, Category="Weapon|Damage")
	TSubclassOf<UDamageType> DamageType;

	TEnumAsByte<EItemRarity> Rarity;
};
