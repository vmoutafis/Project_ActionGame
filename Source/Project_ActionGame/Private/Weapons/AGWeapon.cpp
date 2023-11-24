// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AGWeapon.h"

#include "Characters/AGPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAGWeapon::AAGWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);
	
	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(WeaponMesh);
	DamageCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageCollision->SetUseCCD(true);
}

void AAGWeapon::InitialiseWeapon(AActor* ParentOwner, const float& WeaponDamage)
{
	SetOwner(ParentOwner);
	Damage = WeaponDamage;
}

void AAGWeapon::ActivateDamage()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAGWeapon::DeactivateDamage()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAGWeapon::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AAGWeapon::OnDamageColliderHit);
}

void AAGWeapon::OnDamageColliderHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return;

	AController* OwnerController = Cast<APawn>(GetOwner())->GetController();
	
	UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, this, DamageType);
}
