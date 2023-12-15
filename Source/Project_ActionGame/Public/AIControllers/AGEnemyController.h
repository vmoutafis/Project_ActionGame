// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGAIController.h"
#include "AGEnemyController.generated.h"

UCLASS()
class PROJECT_ACTIONGAME_API AAGEnemyController : public AAGAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAGEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
