// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AGAbilitySystemComponent.h"

#include "AbilitySystem/AGAttributeSet.h"
#include "Characters/AGCharacter.h"

void UAGAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetOwnerAttributes()))
		return;

	// health delegates
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetHealthAttribute()).AddUObject(this, &UAGAbilitySystemComponent::HealthChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetMaxHealthAttribute()).AddUObject(this, &UAGAbilitySystemComponent::HealthChanged);

	// shield delegates
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetShieldAttribute()).AddUObject(this, &UAGAbilitySystemComponent::ShieldChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetMaxShieldAttribute()).AddUObject(this, &UAGAbilitySystemComponent::ShieldChanged);

	// experience delegates
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetMaxExperienceAttribute()).AddUObject(this, &UAGAbilitySystemComponent::ExperienceChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetExperienceAttribute()).AddUObject(this, &UAGAbilitySystemComponent::ExperienceChanged);

	// level delegates
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetLevelAttribute()).AddUObject(this, &UAGAbilitySystemComponent::LevelChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetMaxLevelAttribute()).AddUObject(this, &UAGAbilitySystemComponent::LevelChanged);

	// stats delegates
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetArmourAttribute()).AddUObject(this, &UAGAbilitySystemComponent::StatsChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetBaseDamageAttribute()).AddUObject(this, &UAGAbilitySystemComponent::StatsChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetWeaponDamageAttribute()).AddUObject(this, &UAGAbilitySystemComponent::StatsChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetFireDamageAttribute()).AddUObject(this, &UAGAbilitySystemComponent::StatsChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetFrostDamageAttribute()).AddUObject(this, &UAGAbilitySystemComponent::StatsChanged);
	GetGameplayAttributeValueChangeDelegate(GetOwnerAttributes()->GetMagicResistAttribute()).AddUObject(this, &UAGAbilitySystemComponent::StatsChanged);
}

const UAGAttributeSet* UAGAbilitySystemComponent::GetOwnerAttributes() const
{
	if (!IsValid(GetOwner()))
		return nullptr;
	
	const AAGCharacter* CharRef =  Cast<AAGCharacter>(GetOwner());

	if (!IsValid(CharRef))
		return nullptr;

	return CharRef->GetAttributes();
}

void UAGAbilitySystemComponent::HealthChanged(const FOnAttributeChangeData& Data)
{
	Delegate_OnHealthChanged.Broadcast(GetOwnerAttributes()->GetHealth(), GetOwnerAttributes()->GetMaxHealth());
	Delegate_OnAnyStatChanged.Broadcast(Data.Attribute, Data.NewValue);
}

void UAGAbilitySystemComponent::ShieldChanged(const FOnAttributeChangeData& Data)
{
	Delegate_OnHealthChanged.Broadcast(GetOwnerAttributes()->GetShield(), GetOwnerAttributes()->GetMaxShield());
	Delegate_OnAnyStatChanged.Broadcast(Data.Attribute, Data.NewValue);
}

void UAGAbilitySystemComponent::ExperienceChanged(const FOnAttributeChangeData& Data)
{
	Delegate_OnExperienceChanged.Broadcast(GetOwnerAttributes()->GetExperience(), GetOwnerAttributes()->GetMaxExperience());
	Delegate_OnAnyStatChanged.Broadcast(Data.Attribute, Data.NewValue);
}

void UAGAbilitySystemComponent::LevelChanged(const FOnAttributeChangeData& Data)
{
	Delegate_OnLevelChanged.Broadcast(GetOwnerAttributes()->GetLevel(), GetOwnerAttributes()->GetMaxLevel());
	Delegate_OnAnyStatChanged.Broadcast(Data.Attribute, Data.NewValue);
}

void UAGAbilitySystemComponent::StatsChanged(const FOnAttributeChangeData& Data)
{
	Delegate_OnAnyStatChanged.Broadcast(Data.Attribute, Data.NewValue);
}

void UAGAbilitySystemComponent::OnHealthDamageTaken(float Damage)
{
	Delegate_OnHealthDamageTaken.Broadcast(Damage);
}

void UAGAbilitySystemComponent::OnShieldDamageTaken(float Damage)
{
	Delegate_OnShieldDamageTaken.Broadcast(Damage);
}
