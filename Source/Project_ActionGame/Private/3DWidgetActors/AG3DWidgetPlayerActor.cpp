// Fill out your copyright notice in the Description page of Project Settings.


#include "3DWidgetActors/AG3DWidgetPlayerActor.h"

AAG3DWidgetPlayerActor::AAG3DWidgetPlayerActor()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	WeaponSocketName = FName(FString("Socket_Weapon"));
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(Mesh, WeaponSocketName);
}

void AAG3DWidgetPlayerActor::SetWeapon(USkeletalMesh* NewMesh)
{
	WeaponMesh->SetSkeletalMeshAsset(NewMesh);
}
