// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGCharacter.h"
#include "AGNPCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class PROJECT_ACTIONGAME_API AAGNPCharacter : public AAGCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAGNPCharacter();

	UBehaviorTree* GetBehaviourTree() const { return BehaviorTree; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTree;
	
};
