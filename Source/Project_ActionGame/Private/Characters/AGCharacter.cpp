// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacter.h"

#include "AGDataTypes.h"
#include "AGHelperFunctions.h"
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
	AirAttackCombo = 0;
	bIsBasicAttacking = false;
	bIsAirAttacking = false;

	AirComboCooldownTime = 2.0f;
	bCanAirComboMulti = false;
	
	ActorLerpRotationSpeed = 0.0f;
	
	JumpStartAnim = nullptr;
	JumpStartCombatAnim = nullptr;

	ClearWeaponDamageEffect = nullptr;

	GetCharacterMovement()->AirControl = 1.0f;

	MeleeAttackRange = 150.0f;
	RangedAttackRange = 1000.0f;
	
	bDoesntRequireWeapon = false;
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

	ClearWeaponDamage();
	
	if (Item == nullptr)
	{
		Weapon->SetChildActorClass(nullptr);
		return;
	}

	const AAGDLootGearWeapon* WeaponLoot = Cast<AAGDLootGearWeapon>(Item->LootClass.GetDefaultObject());
	
	if (!IsValid(WeaponLoot) || !IsValid(WeaponLoot->WeaponClass))
		return;

	Weapon->SetChildActorClass(WeaponLoot->WeaponClass);

	AAGWeapon* WeaponRef = Cast<AAGWeapon>(Weapon->GetChildActor());
	
	if (!IsValid(WeaponRef))
		return;

	WeaponRef->InitialiseWeapon(Item->Rarity);
	const TSubclassOf<UAGGameplayEffect> EffectClass = WeaponRef->GetWeaponStatsEffect();

	if (!IsValid(EffectClass))
		return;
	
	const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 0.0f, ContextHandle);

	const FGameplayTag WeaponDamageTag = FGameplayTag::RequestGameplayTag(FName("Weapon.Damage.Base"));
	
	if (WeaponDamageTag.IsValid())
		SpecHandle.Data->SetSetByCallerMagnitude(WeaponDamageTag, WeaponRef->GetFullWeaponDamage());

	TArray<FName> ElementNames = { FName("Weapon.Damage.Fire"), FName("Weapon.Damage.Frost") };
	TArray<TEnumAsByte<ESpecialDamageTypes>> ElementTypes = UAGHelperFunctions::GetSpecialDamageTypesAsArray();

	for (uint8 i = 0; i < ElementNames.Num(); ++i)
	{
		FGameplayTag ElementalDamageTag = FGameplayTag::RequestGameplayTag(ElementNames[i]);

		if (ElementalDamageTag.IsValid())
			SpecHandle.Data->SetSetByCallerMagnitude(ElementalDamageTag, WeaponRef->GetElementalDamage(ElementTypes[i]));	
	}

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
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
	if (bIsBasicAttacking || !HasWeaponEquipped() || bIsAirAttacking)
		return false;

	if (!IsWeaponUnsheathed() && !bDoesntRequireWeapon)
		UnsheathWeapon(true);

	if (GetWorldTimerManager().IsTimerActive(TH_SheathWeaponTimer))
		GetWorldTimerManager().ClearTimer(TH_SheathWeaponTimer);

	bIsBasicAttacking = true;

	float AnimLength = 0.0f;

	if (!GetCharacterMovement()->IsFalling() && BasicAttackAnims.IsValidIndex(BasicAttackCombo))
		AnimLength = PlayAnimMontage(BasicAttackAnims[BasicAttackCombo]);
	else if (GetCharacterMovement()->IsFalling() && BasicAttackAirAnims.IsValidIndex(AirAttackCombo))
	{
		if (GetCharacterMovement()->MovementMode != MOVE_Flying)
			GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		
		AnimLength = PlayAnimMontage(BasicAttackAirAnims[AirAttackCombo]);
		bIsAirAttacking = true;
	}

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

	if (bIsAirAttacking)
	{
		AirAttackCombo++;
		EndAirAttacking();
	}

	if (AirAttackCombo >= BasicAttackAirAnims.Num() && !GetWorldTimerManager().IsTimerActive(TH_AirComboReset) && bCanAirComboMulti)
		GetWorldTimerManager().SetTimer(TH_AirComboReset, this, &AAGCharacter::ResetAirAttackCombo, AirComboCooldownTime);

	bIsBasicAttacking = false;
}

void AAGCharacter::EndBasicAttackCombo()
{
	BasicAttackCombo = 0;
	bIsBasicAttacking = false;

	if (bIsAirAttacking)
		EndAirAttacking();
	
	GetWorldTimerManager().ClearTimer(TH_BasicAttackTimer);
}

void AAGCharacter::ForceCancelAttack()
{
	EndBasicAttackCombo();
	ResetAirAttackCombo();
	CancelActorRotationLerp();
	
	for (UAnimMontage* LAnim : BasicAttackAnims)
	{
		if (LAnim == GetCurrentMontage())
		{
			StopAnimMontage(LAnim);
			break;
		}
	}

	for (UAnimMontage* LAnim : BasicAttackAirAnims)
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
	return IsValid(Weapon->GetChildActorClass()) || bDoesntRequireWeapon;
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

		UAnimMontage* JumpAnimToPlay = JumpStartAnim;

		if (IsWeaponUnsheathed() && IsValid(JumpStartCombatAnim))
			JumpAnimToPlay = JumpStartCombatAnim;
		
		if (IsValid(JumpAnimToPlay))
			PlayAnimMontage(JumpAnimToPlay);

		Jump();
	}
	else
		StopJumping();
}

void AAGCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	ResetAirAttackCombo();
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

void AAGCharacter::EndAirAttacking()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	bIsAirAttacking = false;
}

void AAGCharacter::ResetAirAttackCombo()
{
	AirAttackCombo = 0;
	GetWorldTimerManager().ClearTimer(TH_AirComboReset);
}

void AAGCharacter::ClearWeaponDamage()
{
	if (IsValid(ClearWeaponDamageEffect))
	{
		const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ClearWeaponDamageEffect, 0.0f, ContextHandle);
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

