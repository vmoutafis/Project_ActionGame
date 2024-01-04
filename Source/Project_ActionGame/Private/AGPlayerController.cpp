// Fill out your copyright notice in the Description page of Project Settings.


#include "AGPlayerController.h"

#include "AGHelperFunctions.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "3DWidgetActors/AG3DWidgetPlayerActor.h"
#include "Characters/AGPlayerCharacter.h"
#include "UserWidgets/AGGameMenuWidget.h"
#include "UserWidgets/AGPlayerHUDWidget.h"

AAGPlayerController::AAGPlayerController()
{
	MovementInputVector = FVector2D();

	IA_Camera = nullptr;
	IA_Movement = nullptr;
	IA_BasicAttack = nullptr;
	IA_Interact = nullptr;
	IA_ToggleSheath = nullptr;
	PlayerHUD = nullptr;
	PlayerRef = nullptr;
	Player3DWidget = nullptr;
	GameMenu = nullptr;
	GameMenuClass = nullptr;
	Player3DWidgetClass = nullptr;
}

void AAGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!IMC_Locomotion.IsNull())
				InputSystem->AddMappingContext(IMC_Locomotion.LoadSynchronous(), 0);

			if (!IMC_Camera.IsNull())
				InputSystem->AddMappingContext(IMC_Camera.LoadSynchronous(), 1);

			if (!IMC_Combat.IsNull())
				InputSystem->AddMappingContext(IMC_Combat.LoadSynchronous(), 2);

			if (!IMC_Interact.IsNull())
				InputSystem->AddMappingContext(IMC_Interact.LoadSynchronous(), 3);

			if (!IMC_Interact.IsNull())
				InputSystem->AddMappingContext(IMC_GameMenu.LoadSynchronous(), 4);
		}
	}
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleMovement);
	Input->BindAction(IA_Movement, ETriggerEvent::Canceled, this, &AAGPlayerController::HandleMovement);
	Input->BindAction(IA_Movement, ETriggerEvent::Completed, this, &AAGPlayerController::HandleMovement);
	
	Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleJump);
	
	Input->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleCamera);
	Input->BindAction(IA_BasicAttack, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleBasicAttack);
	Input->BindAction(IA_ToggleSheath, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleWeaponSheath);
	Input->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleInteract);
	Input->BindAction(IA_ToggleGameMenu, ETriggerEvent::Triggered, this, &AAGPlayerController::HandleGameMenu);
}

void AAGPlayerController::ToggleGameMenu()
{
	if (GameMenu->IsInViewport())
	{
		GameMenu->RemoveFromParent();
		SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);
	}
	else
	{
		GameMenu->AddToPlayerScreen();
		SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);
		GameMenu->SetFocus();
	}
}

void AAGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GameMenu) && IsValid(GameMenuClass))
		GameMenu = CreateWidget<UAGGameMenuWidget>(this, GameMenuClass);
	
	if (!IsValid(PlayerHUD) && IsValid(PlayerHUDClass))
		PlayerHUD = CreateWidget<UAGPlayerHUDWidget>(this, PlayerHUDClass);

	PlayerHUD->AddToPlayerScreen();
}

void AAGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetInputMode(FInputModeGameOnly());

	PlayerRef = Cast<AAGPlayerCharacter>(GetPawn());

	if (!IsValid(Player3DWidget))
	{
		Player3DWidget = GetWorld()->SpawnActor<AAG3DWidgetPlayerActor>(Player3DWidgetClass,
			FVector(0.0f, 0.0f, 100000.0f), FRotator(0.0f), FActorSpawnParameters());
	}
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

	PlayerRef->TryWeaponAttack();
}

void AAGPlayerController::HandleWeaponSheath(const FInputActionInstance& Action)
{
	if (!IsValid(PlayerRef))
		return;
	
	if (const bool bPressed = Action.GetValue().Get<bool>())
		PlayerRef->ToggleSheath();
}

void AAGPlayerController::HandleInteract(const FInputActionInstance& Action)
{
	if (!IsValid(PlayerRef))
		return;
	
	if (const bool bPressed = Action.GetValue().Get<bool>())
		PlayerRef->TryInteract();
}

void AAGPlayerController::HandleGameMenu(const FInputActionInstance& Action)
{
	if (!IsValid(GameMenu))
		return;
	
	if (const bool bPressed = Action.GetValue().Get<bool>())
		ToggleGameMenu();
}

void AAGPlayerController::HandleJump(const FInputActionInstance& Action)
{
	if (!IsValid(PlayerRef))
		return;
	
	PlayerRef->TryJump(Action.GetValue().Get<bool>());
}
