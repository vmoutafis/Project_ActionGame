// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/AGGameMode.h"

#include "AGPlayerController.h"
#include "Characters/AGPlayerCharacter.h"

AAGGameMode::AAGGameMode()
{
	PlayerControllerClass = AAGPlayerController::StaticClass();
	DefaultPawnClass = AAGPlayerCharacter::StaticClass();
}
