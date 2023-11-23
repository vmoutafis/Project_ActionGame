// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAGAnimInstance();
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category=Pawn)
	float SpeedXY;

	UPROPERTY(BlueprintReadOnly, Category=Pawn)
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category=Pawn)
	float SpeedZ;
	
	UPROPERTY(BlueprintReadOnly, Category=Character)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category=Character)
	bool IsInAir;

	UPROPERTY(BlueprintReadOnly, Category=Pawn)
	float Direction;
	
};
