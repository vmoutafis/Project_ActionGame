// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AGAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/AGAbilitySystemComponent.h"

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

float UAGAttributeSet::GetApplyDamage() const
{
	return ApplyDamage.GetCurrentValue();
}

void UAGAttributeSet::SetApplyDamage(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAGAbilitySystemComponent* ASC = Cast<UAGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
	
	if (ensure(ASC))
		ASC->SetNumericAttributeBase(GetApplyDamageAttribute(), NewVal);
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
	Delegate_OnLevelUp.Broadcast(GetLevel());

	return true;
}

void UAGAttributeSet::HandleDamage(const FGameplayEffectModCallbackData& Data)
{
	// if the data was an apply damage attribute
	if (Data.EvaluatedData.Attribute != GetApplyDamageAttribute() &&
		Data.EvaluatedData.Attribute != GetFireDamageAttribute() &&
		Data.EvaluatedData.Attribute != GetFrostDamageAttribute())
		return;
	
	float NewHealth = GetHealth();
	float DamageTaken = Data.EvaluatedData.Magnitude;
	TEnumAsByte<auto> DamageType = SDT_None;
	float ShieldDamage = 0.0f;
	float HealthDamage = 0.0f;

	// if the damage was an elemental damage attribute
	if (Data.EvaluatedData.Attribute == GetFireDamageAttribute() ||
		Data.EvaluatedData.Attribute == GetFrostDamageAttribute())
	{
		// store the old shield for carry over
		const float OldShield = GetShield();
		float NewShield = OldShield;

		// if there is a shield
		if (NewShield > 0)
		{
			// set the shield to the reduced amount
			NewShield = NewShield - DamageTaken;
			SetShield(NewShield);

			ShieldDamage = OldShield - NewShield;
				
			// reduce damage by the amount the shield took
			DamageTaken = FMath::Max(DamageTaken - OldShield, 0.0f);
		}

		// set the damage type
		if (Data.EvaluatedData.Attribute == GetFireDamageAttribute())
			DamageType = SDT_Fire;
			
		if (Data.EvaluatedData.Attribute == GetFrostDamageAttribute())
			DamageType = SDT_Fire;
	}
	else // if the damage wasn't elemental
		{
		// reduce the damage based on armour
		DamageTaken = FMath::Max(DamageTaken - GetArmour(), 0.0f);		
		}

	// update the health if damage remaining
	if (DamageTaken > 0)
	{
		NewHealth -= DamageTaken;
		HealthDamage = DamageTaken;
		SetHealth(NewHealth);
	}
		
	Delegate_OnDamageApplied.Broadcast(Data.EvaluatedData.Magnitude, DamageType, ShieldDamage, HealthDamage);
}

void UAGAttributeSet::HandleHealing(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute != GetHealthAttribute())
		return;
	
	const float NewHealth = GetHealth() + Data.EvaluatedData.Magnitude;
	SetHealth(NewHealth);

	Delegate_OnHealed.Broadcast(GetHealth(), Data.EvaluatedData.Magnitude);
}

void UAGAttributeSet::HandleExperience(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute != GetExperienceAttribute())
		return;
	
	float NewValue = GetExperience() + Data.EvaluatedData.Magnitude;
	bool bMaxLevel = false;
	
	if (NewValue >= GetMaxExperience())
	{
		if (TryLevelUp())
			NewValue = NewValue - GetMaxExperience();
		else
		{
			bMaxLevel = true;
			NewValue = GetMaxExperience();
		}
	}

	SetExperience(NewValue);

	if (!bMaxLevel)
		Delegate_OnExperienceGained.Broadcast(Data.EvaluatedData.Magnitude);
}
