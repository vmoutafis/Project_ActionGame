// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGEnemyCharacter.h"

#include "AIControllers/AGEnemyController.h"

AAGEnemyCharacter::AAGEnemyCharacter()
{
	AIControllerClass = AAGEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
