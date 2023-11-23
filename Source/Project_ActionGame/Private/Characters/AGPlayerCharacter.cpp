// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAGPlayerCharacter::AAGPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 600.0f;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	BasicAttackCombo = 0;
	bIsBasicAttacking = false;

	ActorLerpRotationSpeed = 0.0f;
}

bool AAGPlayerCharacter::TryBasicAttack()
{
	if (bIsBasicAttacking || !BasicAttackAnims.IsValidIndex(BasicAttackCombo))
		return false;

	bIsBasicAttacking = true;

	const float AnimLength = PlayAnimMontage(BasicAttackAnims[BasicAttackCombo]);
	
	GetWorldTimerManager().SetTimer(TH_BasicAttackTimer, this, &AAGPlayerCharacter::EndBasicAttackCombo, AnimLength);

	FRotator RotateTo;
	RotateTo.Yaw = GetControlRotation().Yaw;
	
	LerpActorRotation(RotateTo, 5.0f);
	
	return true;
}

void AAGPlayerCharacter::AttackComplete()
{
	BasicAttackCombo++;

	if (BasicAttackCombo >= BasicAttackAnims.Num())
		BasicAttackCombo = 0;
	
	bIsBasicAttacking = false;
}

void AAGPlayerCharacter::EndBasicAttackCombo()
{
	BasicAttackCombo = 0;
	bIsBasicAttacking = false;
	GetWorldTimerManager().ClearTimer(TH_BasicAttackTimer);
}

void AAGPlayerCharacter::ForceCancelAttack()
{
	EndBasicAttackCombo();
	CancelActorRotationLerp();
	
	for (UAnimMontage* LAnim : BasicAttackAnims)
	{
		if (LAnim == GetCurrentMontage())
		{
			StopAnimMontage(LAnim);
			break;
		}
	}
}

void AAGPlayerCharacter::LerpActorRotation(const FRotator& Rotation, const float& Speed)
{
	CancelActorRotationLerp();
	
	FinalActorLerpRotation = Rotation;
	ActorLerpRotationSpeed = Speed;

	GetWorldTimerManager().SetTimer(TH_LerpActorRotation, this, &AAGPlayerCharacter::LerpActorRotationTick, 0.01, true);
}

void AAGPlayerCharacter::LerpActorRotationTick()
{
	const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), FinalActorLerpRotation,
		GetWorld()->DeltaTimeSeconds, ActorLerpRotationSpeed);
	
	SetActorRotation(NewRotation);

	if ((GetActorRotation() - FinalActorLerpRotation).IsNearlyZero(0.1))
		CancelActorRotationLerp();
}

void AAGPlayerCharacter::CancelActorRotationLerp()
{
	GetWorldTimerManager().ClearTimer(TH_LerpActorRotation);
}
