// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGPlayerController.generated.h"

class UAGGameMenuWidget;
class AAG3DWidgetPlayerActor;
class UAGPlayerHUDWidget;
class AAGPlayerCharacter;
class UInputMappingContext;
struct FInputActionInstance;
class UInputAction;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAGPlayerController();
	
	UFUNCTION(BlueprintPure, Category=Player)
	AAGPlayerCharacter* GetPlayerRef() const { return PlayerRef; }

	virtual void SetupInputComponent() override;

	FVector2D GetMovementInputVector() const { return MovementInputVector; }

	void ToggleGameMenu();

	AAG3DWidgetPlayerActor* GetPlayer3DWidget() const { return Player3DWidget; }

	UAGGameMenuWidget* GetGameMenu() const { return GameMenu; }
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void HandleMovement(const FInputActionInstance& Action);

	void HandleCamera(const FInputActionInstance& Action);

	void HandleBasicAttack(const FInputActionInstance& Action);

	void HandleWeaponSheath(const FInputActionInstance& Action);
	
	void HandleInteract(const FInputActionInstance& Action);
	
	void HandleGameMenu(const FInputActionInstance& Action);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Locomotion;

	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Camera;

	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Combat;

	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Interact;

	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_GameMenu;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_Movement;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_Camera;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_BasicAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_ToggleSheath;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_ToggleGameMenu;

	UPROPERTY()
	AAGPlayerCharacter* PlayerRef;

	FVector2D MovementInputVector;

	UPROPERTY(EditDefaultsOnly, Category="UI|HUD")
	TSubclassOf<UAGPlayerHUDWidget> PlayerHUDClass;

	UPROPERTY()
	UAGPlayerHUDWidget* PlayerHUD;

	UPROPERTY(EditDefaultsOnly, Category="UI|GameMenu")
	TSubclassOf<UAGGameMenuWidget> GameMenuClass;

	UPROPERTY()
	UAGGameMenuWidget* GameMenu;

	UPROPERTY(EditDefaultsOnly, Category="UI|GameMenu")
	TSubclassOf<AAG3DWidgetPlayerActor> Player3DWidgetClass;
	
	UPROPERTY()
	AAG3DWidgetPlayerActor* Player3DWidget;

};
