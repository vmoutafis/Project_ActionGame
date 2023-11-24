// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacter.h"

// Sets default values
AAGCharacter::AAGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSocketName = FName("Socket_Weapon");
	SheathSocketName = FName("Socket_Sheath");
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Player Weapon"));
	Weapon->SetupAttachment(GetMesh(), SheathSocketName);

	bIsWeaponUnsheathed = false;
	bIsSheathingWeapon = false;

	BasicAttackCombo = 0;
	bIsBasicAttacking = false;

	ActorLerpRotationSpeed = 0.0f;
}

void AAGCharacter::AttachWeaponToHand()
{
	const FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	
	Weapon->AttachToComponent(GetMesh(), TransformRules, WeaponSocketName);

	bIsWeaponUnsheathed = true;
	bIsSheathingWeapon = false;
	
	GetWorldTimerManager().ClearTimer(TH_UnsheathWeaponTimer);
}

void AAGCharacter::AttachWeaponToSheath()
{
	const FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	
	Weapon->AttachToComponent(GetMesh(), TransformRules, SheathSocketName);

	bIsWeaponUnsheathed = false;
	bIsSheathingWeapon = false;

	GetWorldTimerManager().ClearTimer(TH_UnsheathWeaponTimer);
}

void AAGCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AttachWeaponToSheath();
}

void AAGCharacter::SheathWeapon(const bool& bInstant)
{
	if (!IsWeaponUnsheathed()  ||
		GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() ||
		bIsBasicAttacking)
		return;
	
	if (!IsValid(SheathWeaponAnim) || bInstant)
	{
		AttachWeaponToSheath();
		return;
	}

	bIsSheathingWeapon = true;
	
	const float AnimTime = PlayAnimMontage(SheathWeaponAnim);

	GetWorldTimerManager().ClearTimer(TH_UnsheathWeaponTimer);
	GetWorldTimerManager().SetTimer(TH_SheathWeaponTimer, this, &AAGCharacter::AttachWeaponToSheath, AnimTime);
}

void AAGCharacter::ToggleSheath()
{
	if (bIsSheathingWeapon)
		return;
	
	if (IsWeaponUnsheathed())
		SheathWeapon();
	else
		UnsheathWeapon();
}

void AAGCharacter::UnsheathWeapon(const bool& bInstant)
{
	if (IsWeaponUnsheathed() ||
		GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() ||
		bIsBasicAttacking)
		return;
	
	if (!IsValid(UnsheathWeaponAnim) || bInstant)
	{
		AttachWeaponToHand();
		return;
	}

	bIsSheathingWeapon = true;

	const float AnimTime = PlayAnimMontage(UnsheathWeaponAnim);
	
	GetWorldTimerManager().ClearTimer(TH_SheathWeaponTimer);
	GetWorldTimerManager().SetTimer(TH_UnsheathWeaponTimer, this, &AAGCharacter::AttachWeaponToHand, AnimTime);
}

bool AAGCharacter::TryBasicAttack()
{
	if (bIsBasicAttacking || !BasicAttackAnims.IsValidIndex(BasicAttackCombo) || !IsWeaponUnsheathed())
		return false;

	bIsBasicAttacking = true;

	const float AnimLength = PlayAnimMontage(BasicAttackAnims[BasicAttackCombo]);
	
	GetWorldTimerManager().SetTimer(TH_BasicAttackTimer, this, &AAGCharacter::EndBasicAttackCombo, AnimLength);

	FRotator RotateTo;
	RotateTo.Yaw = GetControlRotation().Yaw;
	
	LerpActorRotation(RotateTo, 5.0f);
	
	return true;
}

void AAGCharacter::AttackComplete()
{
	BasicAttackCombo++;

	if (BasicAttackCombo >= BasicAttackAnims.Num())
		BasicAttackCombo = 0;
	
	bIsBasicAttacking = false;
}

void AAGCharacter::EndBasicAttackCombo()
{
	BasicAttackCombo = 0;
	bIsBasicAttacking = false;
	GetWorldTimerManager().ClearTimer(TH_BasicAttackTimer);
}

void AAGCharacter::ForceCancelAttack()
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

void AAGCharacter::LerpActorRotation(const FRotator& Rotation, const float& Speed)
{
	CancelActorRotationLerp();
	
	FinalActorLerpRotation = Rotation;
	ActorLerpRotationSpeed = Speed;

	GetWorldTimerManager().SetTimer(TH_LerpActorRotation, this, &AAGCharacter::LerpActorRotationTick, 0.01, true);
}

void AAGCharacter::LerpActorRotationTick()
{
	const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), FinalActorLerpRotation,
		GetWorld()->DeltaTimeSeconds, ActorLerpRotationSpeed);
	
	SetActorRotation(NewRotation);

	if ((GetActorRotation() - FinalActorLerpRotation).IsNearlyZero(0.1))
		CancelActorRotationLerp();
}

void AAGCharacter::CancelActorRotationLerp()
{
	GetWorldTimerManager().ClearTimer(TH_LerpActorRotation);
}

