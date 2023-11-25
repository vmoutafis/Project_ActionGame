// Fill out your copyright notice in the Description page of Project Settings.


#include "3DWidgetActors/AG3DWidgetActor.h"

#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AAG3DWidgetActor::AAG3DWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Root Transform"));
	SetRootComponent(RootTransform);

	RenderTarget = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture 2D"));
	RenderTarget->SetupAttachment(RootComponent);
	RenderTarget->ProjectionType = ECameraProjectionMode::Orthographic;
	RenderTarget->OrthoWidth = 256.0f;
}

