// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAGPlayerCharacter::AAGPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 600.0f;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}
