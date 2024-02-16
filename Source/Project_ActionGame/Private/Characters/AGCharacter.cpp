// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacter.h"

#include "AGDataTypes.h"
#include "AGHelperFunctions.h"
#include "KismetAnimationLibrary.h"
#include "AbilitySystem/AGAbilitySystemComponent.h"
#include "Loot/AGDLootGearWeapon.h"
#include "Weapons/AGWeapon.h"
#include "AbilitySystem/AGAttributeSet.h"
#include "AbilitySystem/AGGameplayEffect.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/AGWeaponMelee.h"
#include "Weapons/AGWeaponRanged.h"

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
	
	ActorLerpRotationDuration = 0.0f;
	ActorLerpRotationAlpha = 0.0f;

	ClearWeaponDamageEffect = nullptr;

	GetCharacterMovement()->AirControl = 1.0f;

	MeleeAttackRange = 150.0f;
	RangedAttackRange = 1000.0f;

	bBasicAttackCooldown = false;

	ActiveWeaponSlot = 0;
}

void AAGCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bLerpActorRotation)
	{
		ActorLerpRotationAlpha += DeltaSeconds / std::max(ActorLerpRotationDuration, 0.001f);
		
		FRotator LerpRotation = FMath::Lerp(StartActorLerpRotation, FinalActorLerpRotation, ActorLerpRotationAlpha);

		SetActorRotation(LerpRotation);

		if (ActorLerpRotationAlpha >= 1.0f)
			CancelActorRotationLerp();
	}
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
	if (Cast<AAGDLootGearWeapon>(Item->LootClass.GetDefaultObject())->WeaponClass == Weapon->GetChildActor()->GetClass())
		return;
	
	ForceCancelAttack();
	//SheathWeapon(true);

	ClearWeaponDamage();
	
	if (Item == nullptr)
	{
		SheathWeapon(true);
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

void AAGCharacter::AddToWeaponEquippedSlot(FInventoryItem* Item, int Slot)
{
	if (!WeaponInventory.IsValidIndex(Slot))
		return;
	
	WeaponInventory[Slot] = Item;
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

bool AAGCharacter::TryWeaponAttack()
{
	if (bIsBasicAttacking || !HasWeaponEquipped() || bIsAirAttacking || bBasicAttackCooldown)
		return false;

	if (!IsWeaponUnsheathed())
		UnsheathWeapon(true);

	if (GetWorldTimerManager().IsTimerActive(TH_SheathWeaponTimer))
		GetWorldTimerManager().ClearTimer(TH_SheathWeaponTimer);

	bIsBasicAttacking = true;	

	float AnimLength = 0.0f;

	if (MeleeWeaponEquipped())
	{
		if (!GetCharacterMovement()->IsFalling() && GetEquippedWeapon()->GetAttackAnims().IsValidIndex(BasicAttackCombo))
			AnimLength = PlayAnimMontage(GetEquippedWeapon()->GetAttackAnims()[BasicAttackCombo]);
		else if (GetCharacterMovement()->IsFalling() && GetMeleeWeapon()->GetAirAttackAnims().IsValidIndex(AirAttackCombo))
		{
			if (GetCharacterMovement()->MovementMode != MOVE_Flying)
				GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		
			AnimLength = PlayAnimMontage(GetMeleeWeapon()->GetAirAttackAnims()[AirAttackCombo]);
			bIsAirAttacking = true;
		}	
	}

	if (AnimLength <= 0.0f) {
		EndBasicAttackCombo();
		return false;
	}

	GetWorldTimerManager().SetTimer(TH_BasicAttackTimer, this, &AAGCharacter::EndBasicAttackCombo, AnimLength);

	if (RangedWeaponEquipped())
		return true;
	
	FRotator RotateTo;
	RotateTo.Yaw = GetControlRotation().Yaw;
	
	LerpActorRotation(RotateTo, 0.2f);
	
	return true;
}

void AAGCharacter::AttackComplete()
{
	BasicAttackCombo++;

	if (BasicAttackCombo >= GetEquippedWeapon()->GetAttackAnims().Num())
		BasicAttackCombo = 0;

	if (bIsAirAttacking)
	{
		AirAttackCombo++;
		EndAirAttacking();
	}

	bIsBasicAttacking = false;

	if (!MeleeWeaponEquipped())
		return;
	
	if (AirAttackCombo >= GetMeleeWeapon()->GetAirAttackAnims().Num() && !GetWorldTimerManager().IsTimerActive(TH_AirComboReset) && bCanAirComboMulti)
		GetWorldTimerManager().SetTimer(TH_AirComboReset, this, &AAGCharacter::ResetAirAttackCombo, AirComboCooldownTime);

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
	CooldownBasicAttack(0.2f);
	EndBasicAttackCombo();
	ResetAirAttackCombo();
	CancelActorRotationLerp();

	if (!IsValid(GetEquippedWeapon()))
		return;
	
	for (UAnimMontage* LAnim : GetEquippedWeapon()->GetAttackAnims())
	{
		if (LAnim == GetCurrentMontage())
		{
			StopAnimMontage(LAnim);
			break;
		}
	}

	if (!MeleeWeaponEquipped())
		return;
	
	for (UAnimMontage* LAnim : GetMeleeWeapon()->GetAirAttackAnims())
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
	return IsValid(Weapon->GetChildActor());
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

	UAnimMontage* LandAnimToPlay = LandAnim;
	
	if (IsWeaponUnsheathed() && IsValid(LandCombatAnim))
		LandAnimToPlay = LandCombatAnim;
	
	if (IsValid(LandAnimToPlay))
		GetMesh()->GetAnimInstance()->Montage_Play(LandAnimToPlay);
	else
		UE_LOG(LogTemp, Warning, TEXT("AGCharacter | No valid land animation."))
	
	ResetAirAttackCombo();
	EndBasicAttackCombo();
}

AAGWeapon* AAGCharacter::GetEquippedWeapon() const
{
	if (!HasWeaponEquipped())
		return nullptr;

	return Cast<AAGWeapon>(Weapon->GetChildActor());
}

bool AAGCharacter::RangedWeaponEquipped() const
{
	return IsValid(Cast<AAGWeaponRanged>(GetEquippedWeapon()));
}

bool AAGCharacter::MeleeWeaponEquipped() const
{
	return IsValid(Cast<AAGWeaponMelee>(GetEquippedWeapon()));
}

AAGWeaponMelee* AAGCharacter::GetMeleeWeapon() const
{
	if (!HasWeaponEquipped())
		return nullptr;

	if (!MeleeWeaponEquipped())
		return nullptr;

	return Cast<AAGWeaponMelee>(GetEquippedWeapon());
}

AAGWeaponRanged* AAGCharacter::GetRangedWeapon() const
{
	if (!HasWeaponEquipped())
		return nullptr;

	if (!RangedWeaponEquipped())
		return nullptr;

	return Cast<AAGWeaponRanged>(GetEquippedWeapon());
}

TEnumAsByte<EWeaponTypes> AAGCharacter::GetEquippedWeaponType() const
{
	if (!HasWeaponEquipped())
		return EWeaponTypes::WT_None;

	return GetEquippedWeapon()->GetWeaponType();
}

void AAGCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	UAnimMontage* JumpAnimToPlay = GetJumpStartAnim();
		
	if (IsValid(JumpAnimToPlay))
		PlayAnimMontage(JumpAnimToPlay);
	else
		UE_LOG(LogTemp, Warning, TEXT("AGCharacter | No valid jump animations."))
}

void AAGCharacter::SwitchWeapon()
{
	ActiveWeaponSlot++;

	if (ActiveWeaponSlot > WeaponInventory.Num() - 1)
		ActiveWeaponSlot = 0;

	EquipWeapon(WeaponInventory[ActiveWeaponSlot]);
}

void AAGCharacter::LerpActorRotation(const FRotator& Rotation, const float& Duration)
{
	StartActorLerpRotation = GetActorRotation();
	FinalActorLerpRotation = Rotation;
	ActorLerpRotationDuration = Duration;
	bLerpActorRotation = true;
	ActorLerpRotationAlpha = 0.0f;

	if (Duration > 0.0f)
		GetWorldTimerManager().SetTimer(TH_LerpActorRotation, this, &AAGCharacter::CancelActorRotationLerp, Duration, true);
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

UAnimMontage* AAGCharacter::GetJumpStartAnim() const
{
	TArray<UAnimMontage*> JumpAnims = JumpStartAnims;
	
	if (IsWeaponUnsheathed())
		JumpAnims = JumpStartCombatAnims;

	if (JumpAnims.IsEmpty())
		return nullptr;

	UAnimMontage* AnimToPlay = JumpAnims[0];
	const float Direction = UKismetAnimationLibrary::CalculateDirection(GetVelocity(), GetActorRotation());

	if (Direction >= -45.0f && Direction <= 45.0f)
	{
		if (JumpAnims.IsValidIndex(0))
			AnimToPlay = JumpAnims[0];
	}
	else if (Direction > -125.0f && Direction < -45.0f)
	{
		if (JumpAnims.IsValidIndex(1))
			AnimToPlay = JumpAnims[1];
	}
	else if (Direction > 45.0f && Direction < 125.0f)
	{
		if (JumpAnims.IsValidIndex(2))
			AnimToPlay = JumpAnims[2];
	}
	else if (JumpAnims.IsValidIndex(3))
		AnimToPlay = JumpAnims[3];
	
	return AnimToPlay;
}

void AAGCharacter::CooldownBasicAttack(float Duration)
{
	bBasicAttackCooldown = true;

	if (Duration > 0.0f)
		GetWorld()->GetTimerManager().SetTimer(TH_BasicAttackCooldown, this, &AAGCharacter::EnableBasicAttack, Duration);
}

void AAGCharacter::EnableBasicAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(TH_BasicAttackCooldown);
	bBasicAttackCooldown = false;
}

void AAGCharacter::CancelActorRotationLerp()
{
	GetWorld()->GetTimerManager().ClearTimer(TH_LerpActorRotation);
	bLerpActorRotation = false;
}

