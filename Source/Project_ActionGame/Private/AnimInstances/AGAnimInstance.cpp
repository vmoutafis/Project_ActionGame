// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/AGAnimInstance.h"

#include "AGDataTypes.h"
#include "KismetAnimationLibrary.h"
#include "Characters/AGCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

UAGAnimInstance::UAGAnimInstance()
{
	Speed = SpeedXY = SpeedZ =  0.0f;
	IsFalling = IsInAir = false;
	bIsWeaponUnsheathed = false;
	CharacterMovementMode = MOVE_Walking;
	Direction = 0.0f;
	EquippedWeaponType = EWeaponTypes::WT_None;
}

void UAGAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!IsValid(TryGetPawnOwner()))
		return;

	Speed = TryGetPawnOwner()->GetVelocity().Length();

	const FVector VelocityXY = FVector(TryGetPawnOwner()->GetVelocity().X, TryGetPawnOwner()->GetVelocity().Y, 0.0f);
	SpeedXY = VelocityXY.Length();

	SpeedZ = TryGetPawnOwner()->GetVelocity().Z;

	Direction = UKismetAnimationLibrary::CalculateDirection(TryGetPawnOwner()->GetVelocity(), TryGetPawnOwner()->GetActorRotation());
	
	if (const ACharacter* CharRef = Cast<ACharacter>(TryGetPawnOwner()))
	{
		IsFalling = CharRef->GetMovementComponent()->IsFalling();
		IsInAir = CharRef->GetMovementComponent()->IsFalling();

		CharacterMovementMode = CharRef->GetCharacterMovement()->MovementMode;
	}
	else
	{
		IsFalling = SpeedZ < 0.0f;
		IsInAir = SpeedZ != 0.0f;
	}

	if (const AAGCharacter* AGCharRef = Cast<AAGCharacter>(TryGetPawnOwner()))
	{
		bIsWeaponUnsheathed = AGCharRef->IsWeaponUnsheathed();
		EquippedWeaponType = AGCharRef->GetEquippedWeaponType();
	}
}

void UAGAnimInstance::SwitchWeaponSheath(bool Unsheath)
{
	if (AAGCharacter* CharRef = Cast<AAGCharacter>(TryGetPawnOwner()))
	{
		if (std::move(Unsheath))
			CharRef->AttachWeaponToHand();
		else
			CharRef->AttachWeaponToSheath();
	}
}
