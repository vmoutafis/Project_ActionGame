// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/AGAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UAGAnimInstance::UAGAnimInstance()
{
	Speed = SpeedXY = SpeedZ =  0.0f;
	IsFalling = IsInAir = false;
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
	}
	else
	{
		IsFalling = SpeedZ < 0.0f;
		IsInAir = SpeedZ != 0.0f;
	}
	
}
