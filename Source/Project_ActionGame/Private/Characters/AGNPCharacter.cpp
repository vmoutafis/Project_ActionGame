// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGNPCharacter.h"

#include "AIControllers/AGAIController.h"


// Sets default values
AAGNPCharacter::AAGNPCharacter()
{
	AIControllerClass = AAGAIController::StaticClass();
}

