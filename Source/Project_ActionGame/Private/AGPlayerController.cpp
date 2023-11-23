// Fill out your copyright notice in the Description page of Project Settings.


#include "AGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/AGPlayerCharacter.h"

void AAGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!IMC_Locomotion.IsNull())
			{
				InputSystem->AddMappingContext(IMC_Locomotion.LoadSynchronous(), 0);
			}

			if (!IMC_Camera.IsNull())
			{
				InputSystem->AddMappingContext(IMC_Camera.LoadSynchronous(), 0);
			}
		}
	}
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleMovement);
	Input->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleCamera);
}

void AAGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerRef = Cast<AAGPlayerCharacter>(GetPawn());
}

void AAGPlayerController::HandleMovement(const FInputActionInstance& Action)
{
	if (!IsValid(PlayerRef))
		return;
	
	const FVector2D Axis = Action.GetValue().Get<FVector2D>();
	const FRotator RotYaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	PlayerRef->AddMovementInput(RotYaw.Vector(), Axis.X);
	PlayerRef->AddMovementInput(RotYaw.RotateVector(FVector::RightVector), Axis.Y);
}

void AAGPlayerController::HandleCamera(const FInputActionInstance& Action)
{
	const FVector2D Axis = Action.GetValue().Get<FVector2D>();

	AddYawInput(Axis.X);
	AddPitchInput(-Axis.Y);
}
