// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_ActionGameGameMode.h"
#include "Project_ActionGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_ActionGameGameMode::AProject_ActionGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
