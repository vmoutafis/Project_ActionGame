// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGPlayerCharacter.h"

#include "AGCustomObjectTraceChannels.h"
#include "AGHelperFunctions.h"
#include "AGPlayerController.h"
#include "3DWidgetActors/AG3DWidgetPlayerActor.h"
#include "AbilitySystem/AGAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Loot/AGLoot.h"
#include "UserWidgets/AGPlayerHealthWidget.h"
#include "UserWidgets/AGPlayerHUDWidget.h"
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

	GetCharacterMovement()->JumpZVelocity = 720.0f;
	GetCharacterMovement()->GravityScale = 1.5f;
}

void AAGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	LootCollider->OnComponentBeginOverlap.AddDynamic(this, &AAGPlayerCharacter::OnLootColliderOverlapped);
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

void AAGPlayerCharacter::MovePlayer(FVector2D Axis)
{
	const FRotator RotYaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	AddMovementInput(RotYaw.Vector(), Axis.X);
	AddMovementInput(RotYaw.RotateVector(FVector::RightVector), Axis.Y);

	if (Axis.SquaredLength() > 0.0f)
		GetCharacterMovement()->bOrientRotationToMovement = false;
	else
		GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AAGPlayerCharacter::OnLootColliderOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

UAGPlayerHUDWidget* AAGPlayerCharacter::GetPlayerHUD() const
{
	const AAGPlayerController* PC = Cast<AAGPlayerController>(GetController());

	if (!IsValid(PC))
		return nullptr;

	if (!IsValid(PC->GetPlayerHUD()))
		UAGHelperFunctions::AGSimpleWarning("Player HUD not found.");

	return PC->GetPlayerHUD();
}

void AAGPlayerCharacter::UpdateHealthUI()
{
	if (!IsValid(GetPlayerHUD()))
		return;

	if (!IsValid(GetPlayerHUD()->GetPlayerHealthWidget()))
		return;

	if (IsValid(Attributes))
		GetPlayerHUD()->GetPlayerHealthWidget()->SetHealth(Attributes->GetHealth(), Attributes->GetMaxHealth());
}

void AAGPlayerCharacter::UpdateShieldUI()
{
	if (!IsValid(GetPlayerHUD()))
		return;

	if (!IsValid(GetPlayerHUD()->GetPlayerHealthWidget()))
		return;

	if (IsValid(Attributes))
		GetPlayerHUD()->GetPlayerHealthWidget()->SetShield(Attributes->GetShield(), Attributes->GetMaxShield());
}

void AAGPlayerCharacter::UpdateExperienceUI()
{
	if (!IsValid(GetPlayerHUD()))
		return;

	if (!IsValid(GetPlayerHUD()->GetPlayerHealthWidget()))
		return;

	if (IsValid(Attributes))
		GetPlayerHUD()->GetPlayerHealthWidget()->SetExperience(Attributes->GetExperience(), Attributes->GetMaxExperience());
}

void AAGPlayerCharacter::UpdateLevelUI()
{
	if (!IsValid(GetPlayerHUD()))
		return;

	if (!IsValid(GetPlayerHUD()->GetPlayerHealthWidget()))
		return;

	if (IsValid(Attributes))
		GetPlayerHUD()->GetPlayerHealthWidget()->SetLevel(Attributes->GetLevel());
}

void AAGPlayerCharacter::UpdateAllUI()
{
	if (!IsValid(GetPlayerHUD()))
	{
		FTimerHandle HUDTimer;
		GetWorld()->GetTimerManager().SetTimer(HUDTimer, this, &AAGPlayerCharacter::UpdateAllUI, 0.1f);
		return;
	}
	
	UpdateHealthUI();
	UpdateShieldUI();
	UpdateExperienceUI();
	UpdateLevelUI();
}

void AAGPlayerCharacter::AbilitySystemInit()
{
	Super::AbilitySystemInit();

	UpdateAllUI();
}
