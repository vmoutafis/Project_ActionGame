// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AGCharacter.h"
#include "AGPlayerCharacter.generated.h"

class UTimelineComponent;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAGPlayerCharacter : public AAGCharacter
{
	GENERATED_BODY()

public:
	AAGPlayerCharacter();

	// Try to basic attack using the basic attack anims array
	bool TryBasicAttack();

	// Should be run when next combo or anim cancel is allowed
	void AttackComplete();

	// Should be run to tie off attacking or when cancelling attacks
	void EndBasicAttackCombo();

	// Force cancels an attack and resets all required variables
	void ForceCancelAttack();

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

protected:
	UPROPERTY(EditDefaultsOnly, Category=Components)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly, Category="Player|Animations")
	TArray<UAnimMontage*> BasicAttackAnims;

	int BasicAttackCombo;

	bool bIsBasicAttacking;

	FTimerHandle TH_BasicAttackTimer;

	FTimerHandle TH_LerpActorRotation;

	FRotator FinalActorLerpRotation;
	
	float ActorLerpRotationSpeed;
};
