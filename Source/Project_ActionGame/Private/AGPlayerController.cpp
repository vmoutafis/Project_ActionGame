// Fill out your copyright notice in the Description page of Project Settings.


#include "AGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/AGPlayerCharacter.h"

AAGPlayerController::AAGPlayerController()
{
	MovementInputVector = FVector2D();

	IA_Camera = nullptr;
	IA_Movement = nullptr;
	PlayerRef = nullptr;
}

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
				InputSystem->AddMappingContext(IMC_Camera.LoadSynchronous(), 1);
			}

			if (!IMC_Combat.IsNull())
			{
				InputSystem->AddMappingContext(IMC_Combat.LoadSynchronous(), 2);
			}
		}
	}
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleMovement);
	Input->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleCamera);
	Input->BindAction(IA_BasicAttack, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleBasicAttack);
	Input->BindAction(IA_ToggleSheath, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleWeaponSheath);
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

	MovementInputVector.X = Axis.X;
	MovementInputVector.Y = Axis.Y;
}

void AAGPlayerController::HandleCamera(const FInputActionInstance& Action)
{
	const FVector2D Axis = Action.GetValue().Get<FVector2D>();

	AddYawInput(Axis.X);
	AddPitchInput(-Axis.Y);
}

void AAGPlayerController::HandleBasicAttack(const FInputActionInstance& Action)
{
	const bool bPressed = Action.GetValue().Get<bool>();

	if (!bPressed || !IsValid(PlayerRef))
		return;

	PlayerRef->TryBasicAttack();
}

void AAGPlayerController::HandleWeaponSheath(const FInputActionInstance& Action)
{
	if (!IsValid(PlayerRef))
		return;
	
	const bool bPressed = Action.GetValue().Get<bool>();

	if (bPressed)
		PlayerRef->ToggleSheath();
}
