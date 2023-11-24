// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loot/AGLoot.h"
#include "AGLootGear.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API AAGLootGear : public AAGLoot
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
