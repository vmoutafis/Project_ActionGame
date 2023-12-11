// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AGCharacter.generated.h"

class UAGAbilitySystemComponent;
struct FInventoryItem;

UCLASS()
class PROJECT_ACTIONGAME_API AAGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAGCharacter();

	virtual void AttachWeaponToHand();

	virtual void AttachWeaponToSheath();

	virtual void OnConstruction(const FTransform& Transform) override;

	bool IsWeaponUnsheathed() const { return bIsWeaponUnsheathed; }

	void ToggleSheath();

	virtual void EquipWeapon(const FInventoryItem* Item);

	// UnSheath the players weapon by playing the anim
	// Should be an anim notify that runs AttachWeaponToHand()
	void UnsheathWeapon(const bool& bInstant = false);

	// Sheath the players weapon by playing the anim
	// Should be an anim notify that runs AttachWeaponToSheath()
	void SheathWeapon(const bool& bInstant = false);
	
	// Try to basic attack using the basic attack anims array
	bool TryBasicAttack();

	// Should be run when next combo or anim cancel is allowed
	void AttackComplete();

	// Should be run to tie off attacking or when cancelling attacks
	void EndBasicAttackCombo();

	// Force cancels an attack and resets all required variables
	void ForceCancelAttack();

	virtual void BeginPlay() override;

	bool HasWeaponEquipped() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Lerp the actor to a new rotation over time
	// Run CancelActorRotationLerp() to stop
	void LerpActorRotation(const FRotator& Rotation, const float& Speed);

private:
	// Is called by LerpActorRotation as a timer to rotate the actor over time
	// Uses ActorLerpRotation and ActorLerpRotationSpeed to determine
	void LerpActorRotationTick();

	// Cancels the LerpActorRotation timer
	void CancelActorRotationLerp();
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	UChildActorComponent* Weapon;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UAGAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Weapon")
	FName SheathSocketName;

	bool bIsWeaponUnsheathed;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations")
	UAnimMontage* UnsheathWeaponAnim;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations")
	UAnimMontage* SheathWeaponAnim;

	FTimerHandle TH_UnsheathWeaponTimer;
	FTimerHandle TH_SheathWeaponTimer;

	bool bIsSheathingWeapon;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations")
	TArray<UAnimMontage*> BasicAttackAnims;

	int BasicAttackCombo;

	bool bIsBasicAttacking;

	FTimerHandle TH_BasicAttackTimer;

	FTimerHandle TH_LerpActorRotation;

	FRotator FinalActorLerpRotation;
	
	float ActorLerpRotationSpeed;
};
