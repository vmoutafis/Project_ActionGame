// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGAnimInstance.h"
#include "AGPlayerAnimInstance.generated.h"

class AAGPlayerCharacter;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGPlayerAnimInstance : public UAGAnimInstance
{
	GENERATED_BODY()

public:
	UAGPlayerAnimInstance();

	virtual void NativeBeginPlay() override;
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable, Category="Player")
	void AttackComplete() const;

	UFUNCTION(BlueprintCallable, Category="Player")
	void ResetCombo() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category=Player)
	AAGPlayerCharacter* PlayerRef;
	
	UPROPERTY(BlueprintReadOnly, Category=Player)
	FVector2D MovementInputVector;
	
};
