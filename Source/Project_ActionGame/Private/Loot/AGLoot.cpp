// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot/AGLoot.h"

#include "AGCustomObjectTraceChannels.h"
#include "AGGameInstance.h"
#include "AGHelperFunctions.h"
#include "Components/WidgetComponent.h"

// Sets default values
AAGLoot::AAGLoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionObjectType(ECC_Loot);
	Mesh->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_NPC, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Loot, ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Mesh->SetSimulatePhysics(true);

	InteractHUDWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact HUD Icon"));
	InteractHUDWidget->SetupAttachment(RootComponent);
	InteractHUDWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractHUDWidget->SetDrawSize(FVector2D(25.0f, 25.0f));
	InteractHUDWidget->SetVisibility(false);
	InteractHUDWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DisplayName = "Item";
	Icon = nullptr;
	Rarity = EItemRarity::IR_Common;
	CostValue = 1;
}

void AAGLoot::EnableCollectUI(bool bEnable)
{
	if (bEnable)
	{
		InteractHUDWidget->SetVisibility(true);
	}
	else
	{
		InteractHUDWidget->SetVisibility(false);
	}
		
}

void AAGLoot::BeginPlay()
{
	Super::BeginPlay();

	Rarity = UAGHelperFunctions::GetRandomRarity();
}

void AAGLoot::Collect()
{
	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(GI))
		return;

	if (GI->CollectLoot(FInventoryItem(GetClass(), Rarity)))
	{
		EnableCollectUI(false);
		Destroy();
	}
}


