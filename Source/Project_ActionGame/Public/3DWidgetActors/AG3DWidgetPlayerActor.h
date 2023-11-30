// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "3DWidgetActors/AG3DWidgetActor.h"
#include "AG3DWidgetPlayerActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAG3DWidgetPlayerActor : public AAG3DWidgetActor
{
	GENERATED_BODY()

public:
	AAG3DWidgetPlayerActor();

	void SetWeapon(USkeletalMesh* NewMesh);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category=Components)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category=Weapon)
	FName WeaponSocketName;
};
