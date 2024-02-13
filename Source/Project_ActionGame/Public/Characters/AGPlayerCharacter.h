// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AGCharacter.h"
#include "AGPlayerCharacter.generated.h"

class UAGPlayerHUDWidget;
class USphereComponent;
class AAGWeapon;
class UTimelineComponent;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAGPlayerCharacter : public AAGCharacter
{
	GENERATED_BODY()

public:
	AAGPlayerCharacter();

	virtual void BeginPlay() override;

	bool TryInteract();

	virtual void EquipWeapon(const FInventoryItem* Item) override;

	void MovePlayer(FVector2D Axis);
	
protected:
	UFUNCTION()
	void OnLootColliderOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLootColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UAGPlayerHUDWidget* GetPlayerHUD() const;

	void UpdateHealthUI();

	void UpdateShieldUI();

	void UpdateExperienceUI();

	void UpdateLevelUI();

	void UpdateAllUI();

	virtual void AbilitySystemInit() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	USphereComponent* LootCollider;
};
