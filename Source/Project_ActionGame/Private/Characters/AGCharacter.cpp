// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacter.h"

#include "AGDataTypes.h"
#include "AbilitySystem/AGAbilitySystemComponent.h"
#include "Loot/AGDLootGearWeapon.h"
#include "Weapons/AGWeapon.h"
#include "AbilitySystem/AGAttributeSet.h"

// Sets default values
AAGCharacter::AAGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAGAbilitySystemComponent>(TEXT("Ability System"));
	Attributes = AbilitySystemComponent->GetSet<UAGAttributeSet>();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	WeaponSocketName = FName("Socket_Weapon");
	SheathSocketName = FName("Socket_Sheath");
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Player Weapon"));
	Weapon->SetupAttachment(GetMesh(), SheathSocketName);

	bIsWeaponUnsheathed = false;
	bIsSheathingWeapon = false;

	BasicAttackCombo = 0;
	bIsBasicAttacking = false;

	ActorLerpRotationSpeed = 0.0f;
}

void AAGCharacter::AttachWeaponToHand()
{
	const FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	
	Weapon->AttachToComponent(GetMesh(), TransformRules, WeaponSocketName);

	bIsWeaponUnsheathed = true;
	bIsSheathingWeapon = false;
	
	GetWorldTimerManager().ClearTimer(TH_UnsheathWeaponTimer);
}

void AAGCharacter::AttachWeaponToSheath()
{
	const FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	
	Weapon->AttachToComponent(GetMesh(), TransformRules, SheathSocketName);

	bIsWeaponUnsheathed = false;
	bIsSheathingWeapon = false;

	GetWorldTimerManager().ClearTimer(TH_UnsheathWeaponTimer);
}

void AAGCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AttachWeaponToSheath();
}

void AAGCharacter::SheathWeapon(const bool& bInstant)
{
	GetWorldTimerManager().ClearTimer(TH_UnsheathWeaponTimer);
	
	if ((!IsWeaponUnsheathed()  ||
		GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() ||
		bIsBasicAttacking) &&
		!bInstant)
		return;
	
	if (!IsValid(SheathWeaponAnim) || bInstant)
	{
		AttachWeaponToSheath();
		return;
	}

	bIsSheathingWeapon = true;
	
	const float AnimTime = PlayAnimMontage(SheathWeaponAnim);

	GetWorldTimerManager().SetTimer(TH_SheathWeaponTimer, this, &AAGCharacter::AttachWeaponToSheath, AnimTime);
}

void AAGCharacter::ToggleSheath()
{
	if (bIsSheathingWeapon || !HasWeaponEquipped())
		return;
	
	if (IsWeaponUnsheathed())
		SheathWeapon();
	else
		UnsheathWeapon();
}

void AAGCharacter::EquipWeapon(const FInventoryItem* Item)
{
	ForceCancelAttack();
	SheathWeapon(true);

	if (Item == nullptr)
	{
		Weapon->SetChildActorClass(nullptr);
		return;
	}

	const AAGDLootGearWeapon* WeaponLoot = Cast<AAGDLootGearWeapon>(Item->LootClass.GetDefaultObject());
	
	if (!IsValid(WeaponLoot) || !IsValid(WeaponLoot->WeaponClass))
		return;

	Weapon->SetChildActorClass(WeaponLoot->WeaponClass);
}

void AAGCharacter::UnsheathWeapon(const bool& bInstant)
{
	GetWorldTimerManager().ClearTimer(TH_SheathWeaponTimer);

	if ((IsWeaponUnsheathed() ||
		GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() ||
		bIsBasicAttacking) &&
		!bInstant)
		return;
	
	if (!IsValid(UnsheathWeaponAnim) || bInstant)
	{
		AttachWeaponToHand();
		return;
	}

	bIsSheathingWeapon = true;

	const float AnimTime = PlayAnimMontage(UnsheathWeaponAnim);
	
	GetWorldTimerManager().SetTimer(TH_UnsheathWeaponTimer, this, &AAGCharacter::AttachWeaponToHand, AnimTime);
}

bool AAGCharacter::TryBasicAttack()
{
	if (bIsBasicAttacking || !BasicAttackAnims.IsValidIndex(BasicAttackCombo) || !HasWeaponEquipped())
		return false;

	if (!IsWeaponUnsheathed())
		UnsheathWeapon(true);

	bIsBasicAttacking = true;

	const float AnimLength = PlayAnimMontage(BasicAttackAnims[BasicAttackCombo]);
	
	GetWorldTimerManager().SetTimer(TH_BasicAttackTimer, this, &AAGCharacter::EndBasicAttackCombo, AnimLength);

	FRotator RotateTo;
	RotateTo.Yaw = GetControlRotation().Yaw;
	
	LerpActorRotation(RotateTo, 5.0f);
	
	return true;
}

void AAGCharacter::AttackComplete()
{
	BasicAttackCombo++;

	if (BasicAttackCombo >= BasicAttackAnims.Num())
		BasicAttackCombo = 0;
	
	bIsBasicAttacking = false;
}

void AAGCharacter::EndBasicAttackCombo()
{
	BasicAttackCombo = 0;
	bIsBasicAttacking = false;
	GetWorldTimerManager().ClearTimer(TH_BasicAttackTimer);
}

void AAGCharacter::ForceCancelAttack()
{
	EndBasicAttackCombo();
	CancelActorRotationLerp();
	
	for (UAnimMontage* LAnim : BasicAttackAnims)
	{
		if (LAnim == GetCurrentMontage())
		{
			StopAnimMontage(LAnim);
			break;
		}
	}
}

void AAGCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipWeapon(nullptr);
}

bool AAGCharacter::HasWeaponEquipped() const
{
	return IsValid(Weapon->GetChildActorClass());
}

UAbilitySystemComponent* AAGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	

	
}

void AAGCharacter::LerpActorRotation(const FRotator& Rotation, const float& Speed)
{
	CancelActorRotationLerp();
	
	FinalActorLerpRotation = Rotation;
	ActorLerpRotationSpeed = Speed;

	GetWorldTimerManager().SetTimer(TH_LerpActorRotation, this, &AAGCharacter::LerpActorRotationTick, 0.01, true);
}

void AAGCharacter::AbilitySystemInit()
{
	if (!ensure(AbilitySystemComponent))
		return;
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this, &AAGCharacter::HealthOrShieldChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this, &AAGCharacter::HealthOrShieldChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetShieldAttribute()).AddUObject(this, &AAGCharacter::HealthOrShieldChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxShieldAttribute()).AddUObject(this, &AAGCharacter::HealthOrShieldChanged);
}

void AAGCharacter::LerpActorRotationTick()
{
	const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), FinalActorLerpRotation,
		GetWorld()->DeltaTimeSeconds, ActorLerpRotationSpeed);
	
	SetActorRotation(NewRotation);

	if ((GetActorRotation() - FinalActorLerpRotation).IsNearlyZero(0.1))
		CancelActorRotationLerp();
}

void AAGCharacter::CancelActorRotationLerp()
{
	GetWorldTimerManager().ClearTimer(TH_LerpActorRotation);
}

