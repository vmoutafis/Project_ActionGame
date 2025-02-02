// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AGCharacter.generated.h"

enum EWeaponTypes : uint8;
class AAGWeaponRanged;
class AAGWeaponMelee;
class AAGWeapon;
class UAGGameplayEffect;
struct FOnAttributeChangeData;
class UAGAttributeSet;
class UAGAbilitySystemComponent;
struct FInventoryItem;

UCLASS()
class PROJECT_ACTIONGAME_API AAGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAGCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void AttachWeaponToHand();

	virtual void AttachWeaponToSheath();

	virtual void OnConstruction(const FTransform& Transform) override;

	bool IsWeaponUnsheathed() const { return bIsWeaponUnsheathed; }

	void ToggleSheath();

	virtual void EquipWeapon(const FInventoryItem* Item);

	void AddToWeaponEquippedSlot(FInventoryItem* Item, int Slot = 0);

	// UnSheath the players weapon by playing the anim
	// Should be an anim notify that runs AttachWeaponToHand()
	void UnsheathWeapon(const bool& bInstant = false);

	// Sheath the players weapon by playing the anim
	// Should be an anim notify that runs AttachWeaponToSheath()
	void SheathWeapon(const bool& bInstant = false);
	
	// Try to basic attack using the basic attack anims array
	bool TryWeaponAttack();

	// Should be run when next combo or anim cancel is allowed
	void AttackComplete();

	// Should be run to tie off attacking or when cancelling attacks
	void EndBasicAttackCombo();

	// Force cancels an attack and resets all required variables
	void ForceCancelAttack();

	virtual void BeginPlay() override;

	bool HasWeaponEquipped() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	const UAGAttributeSet* GetAttributes() const { return Attributes; }

	virtual void TryJump(const bool& bPressed = true);

	virtual void Landed(const FHitResult& Hit) override;

	AAGWeapon* GetEquippedWeapon() const;

	bool RangedWeaponEquipped() const;

	bool MeleeWeaponEquipped() const;

	AAGWeaponMelee* GetMeleeWeapon() const;

	AAGWeaponRanged* GetRangedWeapon() const;

	TEnumAsByte<EWeaponTypes> GetEquippedWeaponType() const;

	virtual void OnJumped_Implementation() override;

	void SwitchWeapon();

protected:
	// Lerp the actor to a new rotation over time
	// Run CancelActorRotationLerp() to stop - if duration is 0 then this must be called to stop
	void LerpActorRotation(const FRotator& Rotation, const float& Duration = 1.0f);
	
	virtual void AbilitySystemInit();

	void EndAirAttacking();

	void ResetAirAttackCombo();

	void ClearWeaponDamage();

	// gets the relevant jump start animation for directional based jumps
	UAnimMontage* GetJumpStartAnim() const;

	// if no duration is set run EnableBasicAttack() to re-enable
	void CooldownBasicAttack(float Duration);

	UFUNCTION()
	void EnableBasicAttack();
	
private:

	// Cancels the LerpActorRotation
	void CancelActorRotationLerp();
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	UChildActorComponent* Weapon;
	
protected:
	UPROPERTY()
	AActor* Target;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UAGAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|AbilitySystem")
	TArray<TSubclassOf<UAGGameplayEffect>> StarterEffects;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|AbilitySystem")
	TSubclassOf<UAGGameplayEffect> ClearWeaponDamageEffect;
	
	UPROPERTY()
	const UAGAttributeSet* Attributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Weapon")
	FName SheathSocketName;

	bool bIsWeaponUnsheathed;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations|Weapon")
	UAnimMontage* UnsheathWeaponAnim;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations|Weapon")
	UAnimMontage* SheathWeaponAnim;

	// 0 = Forward, 1 = Left, 2 = Right, 3 = Backward
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations|Jump")
	TArray<UAnimMontage*> JumpStartAnims;

	// 0 = Forward, 1 = Left, 2 = Right, 3 = Backward
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations|Jump")
	TArray<UAnimMontage*> JumpStartCombatAnims;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations|Jump")
	UAnimMontage* LandAnim;

	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Animations|Jump")
	UAnimMontage* LandCombatAnim;
	
	FTimerHandle TH_UnsheathWeaponTimer;
	FTimerHandle TH_SheathWeaponTimer;

	bool bIsSheathingWeapon;
	
	// Time before allowed to air combo if CanAirComboMulti is set
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Attacking")
	float AirComboCooldownTime;

	// Can doe more than one air combo
	UPROPERTY(EditDefaultsOnly, Category="Custom Character|Attacking")
	bool bCanAirComboMulti;

	int BasicAttackCombo;
	
	int AirAttackCombo;

	bool bIsBasicAttacking;
	
	bool bIsAirAttacking;

	FTimerHandle TH_BasicAttackTimer;

	FTimerHandle TH_LerpActorRotation;

	FTimerHandle TH_AirComboReset;

	FTimerHandle TH_BasicAttackCooldown;

	FTimerHandle TH_AllowCancelAttack;
	
	// all contribute to the Actor Lerp Rotation
	FRotator FinalActorLerpRotation;
	FRotator StartActorLerpRotation;
	float ActorLerpRotationDuration;
	bool bLerpActorRotation;
	float ActorLerpRotationAlpha;

	float MeleeAttackRange;

	float RangedAttackRange;

	bool bBasicAttackCooldown;

	TArray<FInventoryItem*> WeaponInventory;
	
	int ActiveWeaponSlot;
};
