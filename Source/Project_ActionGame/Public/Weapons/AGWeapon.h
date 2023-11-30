// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "GameFramework/Actor.h"
#include "AGWeapon.generated.h"

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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDamageColliderHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	UBoxComponent* DamageCollision;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon|Damage")
	float BaseDamage;

	float SpecialDamage;

	UPROPERTY(EditDefaultsOnly, Category="Weapon|Damage")
	TSubclassOf<UDamageType> DamageType;

	TEnumAsByte<EItemRarity> Rarity;
};
