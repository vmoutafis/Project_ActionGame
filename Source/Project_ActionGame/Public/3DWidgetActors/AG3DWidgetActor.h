// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG3DWidgetActor.generated.h"

UCLASS()
class PROJECT_ACTIONGAME_API AAG3DWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAG3DWidgetActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category=Components)
	USceneCaptureComponent2D* RenderTarget;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	USceneComponent* RootTransform;
};
