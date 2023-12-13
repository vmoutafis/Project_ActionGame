// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacter.h"

#include "AGDataTypes.h"
#include "AbilitySystem/AGAbilitySystemComponent.h"
#include "Loot/AGDLootGearWeapon.h"
#include "Weapons/AGWeapon.h"
#include "AbilitySystem/AGAttributeSet.h"
#include "AbilitySystem/AGGameplayEffect.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAGCharacter::AAGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAGAbilitySystemComponent>(TEXT("Ability System"));
	Attributes = CreateDefaultSubobject<UAGAttributeSet>(TEXT("Attributes"));

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
	if (bIsBasicAttacking || !HasWeaponEquipped())
		return false;

	if (!IsWeaponUnsheathed())
		UnsheathWeapon(true);

	bIsBasicAttacking = true;

	float AnimLength = 0.0f;

	if (!GetCharacterMovement()->IsFalling() && BasicAttackAnims.IsValidIndex(BasicAttackCombo))
		AnimLength = PlayAnimMontage(BasicAttackAnims[BasicAttackCombo]);
	else if (GetCharacterMovement()->IsFalling() && BasicAttackAirAnims.IsValidIndex(BasicAttackCombo))
		AnimLength = PlayAnimMontage(BasicAttackAirAnims[BasicAttackCombo]);

	if (AnimLength <= 0.0f) {
		EndBasicAttackCombo();
		return false;
	}
	
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

	AbilitySystemInit();

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

void AAGCharacter::TryJump(const bool& bPressed)
{
	if (bIsBasicAttacking)
		return;

	if (!GetCharacterMovement()->IsFalling())
	{
		ForceCancelAttack();
		Jump();
	}
	else
		StopJumping();
}

void AAGCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	EndBasicAttackCombo();
}

void AAGCharacter::LerpActorRotation(const FRotator& Rotation, const float& Speed)
{
	CancelActorRotationLerp();
	
	FinalActorLerpRotation = Rotation;
	ActorLerpRotationSpeed = Speed;

	GetWorldTimerManager().SetTimer(TH_LerpActorRotation, this, &AAGCharacter::LerpActorRotationTick, 0.01f, true);
}

void AAGCharacter::AbilitySystemInit()
{
	if (!ensure(AbilitySystemComponent))
		return;
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	for (auto Effect : StarterEffects)
	{
		const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 0.0f, ContextHandle);

		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}	
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

