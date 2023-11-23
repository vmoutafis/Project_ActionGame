// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGPlayerController.generated.h"

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

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void HandleMovement(const FInputActionInstance& Action);

	void HandleCamera(const FInputActionInstance& Action);

	void HandleBasicAttack(const FInputActionInstance& Action);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Locomotion;

	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Camera;

	UPROPERTY(EditDefaultsOnly, Category="Input|IMC")
	TSoftObjectPtr<UInputMappingContext> IMC_Combat;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_Movement;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_Camera;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* IA_BasicAttack;

	UPROPERTY()
	AAGPlayerCharacter* PlayerRef;

	FVector2D MovementInputVector;
	
};
