// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AGEnemyController.h"


// Sets default values
AAGEnemyController::AAGEnemyController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAGEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAGEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

