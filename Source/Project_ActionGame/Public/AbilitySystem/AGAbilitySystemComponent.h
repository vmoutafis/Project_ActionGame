// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AGAbilitySystemComponent.generated.h"

class UAGAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShieldChanged, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExperienceChanged, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyStatChanged, const FGameplayAttribute&, Attribute, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthDamageTaken, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldDamageTaken, float, Damage);

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// when max or current health changes
	FOnHealthChanged Delegate_OnHealthChanged;
	
	// when max or current shield changes
	FOnHealthChanged Delegate_OnShieldChanged;

	// when experience updates (experience or max experience)
	FOnExperienceChanged Delegate_OnExperienceChanged;

	// if the level has changed (level or max level)
	FOnLevelChanged Delegate_OnLevelChanged;

	// Stats are the any number that can change (e.g. max health, magic resist, armour, etc...)
	FOnAnyStatChanged Delegate_OnAnyStatChanged;

	// When health takes damage from an overridden apply damage attribute
	FOnHealthDamageTaken Delegate_OnHealthDamageTaken;

	// When shield takes damage from an overridden apply damage attribute
	FOnHealthDamageTaken Delegate_OnShieldDamageTaken;

	const UAGAttributeSet* GetOwnerAttributes() const;

	UFUNCTION()
	void OnHealthDamageTaken(float Damage);

	UFUNCTION()
	void OnShieldDamageTaken(float Damage);
	
protected:
	void HealthChanged(const FOnAttributeChangeData& Data);

	void ShieldChanged(const FOnAttributeChangeData& Data);

	void ExperienceChanged(const FOnAttributeChangeData& Data);

	void LevelChanged(const FOnAttributeChangeData& Data);

	void StatsChanged(const FOnAttributeChangeData& Data);
};
