// Fill out your copyright notice in the Description page of Project Settings.


#include "3DWidgetActors/AG3DWidgetPlayerActor.h"

AAG3DWidgetPlayerActor::AAG3DWidgetPlayerActor()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}
