// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGDataTypes.h"
#include "AGLoot.generated.h"

class UWidgetComponent;

UCLASS()
class PROJECT_ACTIONGAME_API AAGLoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGLoot();

	virtual void BeginPlay() override;
	
	virtual void Collect(TEnumAsByte<EGearType> GearType = GT_None);

	void EnableCollectUI(bool bEnable);
	
public:
	UPROPERTY(EditDefaultsOnly, Category=Components)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category=Item)
	FString DisplayName;

	UPROPERTY(EditDefaultsOnly, Category=Item)
	UTexture2D* Icon;
	
	UPROPERTY(EditDefaultsOnly, Category=Item)
	int CostValue;

	UPROPERTY(EditDefaultsOnly, Category=Item)
	TEnumAsByte<EItemRarity> Rarity;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	UWidgetComponent* InteractHUDWidget;
	
};
