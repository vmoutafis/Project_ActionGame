// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/AGPlayerAnimInstance.h"

#include "AGPlayerController.h"
#include "Characters/AGPlayerCharacter.h"

UAGPlayerAnimInstance::UAGPlayerAnimInstance()
{
	MovementInputVector = FVector2D();
	PlayerRef = nullptr;
}

void UAGPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerRef = Cast<AAGPlayerCharacter>(TryGetPawnOwner());
}

void UAGPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!IsValid(PlayerRef))
		return;

	MovementInputVector = Cast<AAGPlayerController>(PlayerRef->GetController())->GetMovementInputVector();
}

void UAGPlayerAnimInstance::AttackComplete() const
{
	if (!IsValid(PlayerRef))
		return;

	PlayerRef->AttackComplete();
}

void UAGPlayerAnimInstance::ResetCombo() const
{
	if (!IsValid(PlayerRef))
		return;

	PlayerRef->EndBasicAttackCombo();
}
