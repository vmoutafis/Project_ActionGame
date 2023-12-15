// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AGAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAGAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
