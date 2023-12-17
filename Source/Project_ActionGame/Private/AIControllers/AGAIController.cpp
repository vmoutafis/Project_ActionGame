// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/AGAIController.h"

#include "AGHelperFunctions.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/AGNPCharacter.h"

void AAGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const AAGNPCharacter* NPCRef = Cast<AAGNPCharacter>(InPawn);

	if (!IsValid(NPCRef))
	{
		UAGHelperFunctions::AGObjectError(this, "Attached Pawn must be derived from AAGNPCharacter.");
		return;
	}

	if (!IsValid(NPCRef->GetBehaviourTree()))
	{
		UAGHelperFunctions::AGObjectError(this, FString(NPCRef->GetName()) + " must be have behaviour tree assigned.");
		return;
	}
	
	RunBehaviorTree(NPCRef->GetBehaviourTree());
}
