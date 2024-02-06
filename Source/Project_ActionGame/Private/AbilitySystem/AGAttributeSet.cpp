// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AGAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/AGAbilitySystemComponent.h"

UAGAttributeSet::UAGAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitBaseDamage(1.0f);
}

float UAGAttributeSet::GetLevel() const
{
	return Level.GetCurrentValue();
}

void UAGAttributeSet::SetLevel(float NewVal)
{
	NewVal = FMath::Clamp(NewVal, 1.0f, GetMaxLevel());

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetLevelAttribute(), NewVal);
}

float UAGAttributeSet::GetMaxLevel() const
{
	return MaxLevel.GetCurrentValue();
}

void UAGAttributeSet::SetMaxLevel(float NewVal)
{
	NewVal = FMath::Max(NewVal, 1.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetMaxLevelAttribute(), NewVal);
}

float UAGAttributeSet::GetExperience() const
{
	return Experience.GetCurrentValue();
}

void UAGAttributeSet::SetExperience(float NewVal)
{
	NewVal = FMath::Clamp(NewVal, 0.0f, GetMaxExperience());

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetExperienceAttribute(), NewVal);
}

float UAGAttributeSet::GetMaxExperience() const
{
	return MaxExperience.GetCurrentValue();
}

void UAGAttributeSet::SetMaxExperience(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetMaxExperienceAttribute(), NewVal);
}

float UAGAttributeSet::GetHealth() const
{
	return Health.GetCurrentValue();
}

void UAGAttributeSet::SetHealth(float NewVal)
{
	NewVal = FMath::Clamp(NewVal, 0.0f, GetMaxHealth());

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetHealthAttribute(), NewVal);
}

float UAGAttributeSet::GetMaxHealth() const
{
	return MaxHealth.GetCurrentValue();
}

void UAGAttributeSet::SetMaxHealth(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetMaxHealthAttribute(), NewVal);
}

float UAGAttributeSet::GetBaseDamage() const
{
	return BaseDamage.GetCurrentValue();
}

void UAGAttributeSet::SetBaseDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetBaseDamageAttribute(), NewVal);
}

float UAGAttributeSet::GetWeaponDamage() const
{
	return WeaponDamage.GetCurrentValue();
}

void UAGAttributeSet::SetWeaponDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetWeaponDamageAttribute(), NewVal);
}

float UAGAttributeSet::GetFireDamage() const
{
	return FireDamage.GetCurrentValue();
}

void UAGAttributeSet::SetFireDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetFireDamageAttribute(), NewVal);
}

float UAGAttributeSet::GetFrostDamage() const
{
	return FrostDamage.GetCurrentValue();
}

void UAGAttributeSet::SetFrostDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetFrostDamageAttribute(), NewVal);
}

float UAGAttributeSet::GetArmour() const
{
	return Armour.GetCurrentValue();
}

void UAGAttributeSet::SetArmour(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetArmourAttribute(), NewVal);
}

float UAGAttributeSet::GetShield() const
{
	return Shield.GetCurrentValue();
}

void UAGAttributeSet::SetShield(float NewVal)
{
	NewVal = FMath::Clamp(NewVal, 0.0f, GetMaxShield());

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetShieldAttribute(), NewVal);
}

float UAGAttributeSet::GetMaxShield() const
{
	return MaxShield.GetCurrentValue();
}

void UAGAttributeSet::SetMaxShield(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetMaxShieldAttribute(), NewVal);
}

float UAGAttributeSet::GetMagicResist() const
{
	return MagicResist.GetCurrentValue();
}

void UAGAttributeSet::SetMagicResist(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetMagicResistAttribute(), NewVal);
}

float UAGAttributeSet::GetApplyPhysicalDamage() const
{
	return ApplyPhysicalDamage.GetCurrentValue();
}

void UAGAttributeSet::SetApplyPhysicalDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetApplyPhysicalDamageAttribute(), NewVal);
}

float UAGAttributeSet::GetApplyFireDamage() const
{
	return ApplyFireDamage.GetCurrentValue();
}

void UAGAttributeSet::SetApplyFireDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetApplyFireDamageAttribute(), NewVal);
}

float UAGAttributeSet::GetApplyFrostDamage() const
{
	return ApplyFrostDamage.GetCurrentValue();
}

void UAGAttributeSet::SetApplyFrostDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetApplyFrostDamageAttribute(), NewVal);
}

void UAGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// if the data evaluated was additive
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Additive)
	{
		HandleDamage(Data);
		HandleHealing(Data);
		HandleExperience(Data);
	}
}

bool UAGAttributeSet::TryLevelUp()
{
	if (GetLevel() >= GetMaxLevel())
		return false;
	
	SetLevel(GetLevel() + 1);

	return true;
}

void UAGAttributeSet::HandleDamage(const FGameplayEffectModCallbackData& Data)
{
	UAGAbilitySystemComponent* ABS = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	check(ABS)

	float FinalDamage = Data.EvaluatedData.Magnitude;

	if (GetShield() > 0.0f)
	{
		const float OldShield = GetShield();
		SetShield(GetShield() - FinalDamage);

		ABS->OnShieldDamageTaken(std::min(FinalDamage, OldShield));

		FinalDamage -= OldShield;
	}

	if (FinalDamage > 0.0f)
	{
		SetHealth(GetHealth() - FinalDamage);
		ABS->OnShieldDamageTaken(FinalDamage);
	}
}

void UAGAttributeSet::HandleHealing(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute != GetHealthAttribute())
		return;
	
	const float NewHealth = GetHealth() + Data.EvaluatedData.Magnitude;
	SetHealth(NewHealth);
}

void UAGAttributeSet::HandleExperience(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute != GetExperienceAttribute())
		return;
	
	float NewValue = GetExperience() + Data.EvaluatedData.Magnitude;
	
	if (NewValue >= GetMaxExperience())
	{
		if (TryLevelUp())
			NewValue = NewValue - GetMaxExperience();
		else
			NewValue = GetMaxExperience();
	}

	SetExperience(NewValue);
}
