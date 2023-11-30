// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGPlayerCharacter.h"

#include "AGCustomObjectTraceChannels.h"
#include "AGPlayerController.h"
#include "3DWidgetActors/AG3DWidgetPlayerActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Loot/AGLoot.h"
#include "Weapons/AGWeapon.h"

AAGPlayerCharacter::AAGPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 600.0f;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->bUsePawnControlRotation = false;
	PlayerCamera->SetConstraintAspectRatio(true);

	LootCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Loot Detection"));
	LootCollider->SetupAttachment(RootComponent);
	LootCollider->SetSphereRadius(300.0f);
	LootCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	LootCollider->SetCollisionResponseToChannel(ECC_Loot, ECR_Overlap);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void AAGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	LootCollider->OnComponentBeginOverlap.AddDynamic(this, &AAGPlayerCharacter::OnLootColliderOverlaped);
	LootCollider->OnComponentEndOverlap.AddDynamic(this, &AAGPlayerCharacter::OnLootColliderEndOverlap);
}

bool AAGPlayerCharacter::TryInteract()
{
	TArray<AActor*> OverlappingActors;
	LootCollider->GetOverlappingActors(OverlappingActors);

	for (AActor* TestActor : OverlappingActors)
	{
		AAGLoot* TestLoot = Cast<AAGLoot>(TestActor);

		if (!IsValid(TestLoot))
			continue;

		TestLoot->Collect();
	}
	
	return true;
}

void AAGPlayerCharacter::EquipWeapon(const FInventoryItem* Item)
{
	Super::EquipWeapon(Item);

	if (!IsValid(Weapon->GetChildActorClass()))
	{
		Cast<AAGPlayerController>(GetController())->GetPlayer3DWidget()->SetWeapon(nullptr);
		return;
	}

	USkeletalMesh* WeaponMesh = Cast<AAGWeapon>(Weapon->GetChildActor())->WeaponMesh->GetSkeletalMeshAsset();

	if (IsValid(WeaponMesh))
		Cast<AAGPlayerController>(GetController())->GetPlayer3DWidget()->SetWeapon(WeaponMesh);
}

void AAGPlayerCharacter::OnLootColliderOverlaped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGLoot* LootItem = Cast<AAGLoot>(OtherActor);
	
	if (!IsValid(LootItem))
		return;
	
	LootItem->EnableCollectUI(true);
}

void AAGPlayerCharacter::OnLootColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAGLoot* LootItem = Cast<AAGLoot>(OtherActor);
	
	if (!IsValid(LootItem))
		return;
	
	LootItem->EnableCollectUI(false);
}
