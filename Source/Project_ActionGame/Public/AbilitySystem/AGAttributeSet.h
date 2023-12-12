// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AGDataTypes.h"
#include "AGAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, float, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDamageApplied, float, Damage, TEnumAsByte<ESpecialDamageTypes>, DamageType, float, ShieldDamage, float, HealthDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealed, float, NewHealth, float, AmountHealed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExperienceGained, float, Amount);

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnLevelUp Delegate_OnLevelUp;

	UPROPERTY(BlueprintAssignable)
	FOnDamageApplied Delegate_OnDamageApplied;

	UPROPERTY(BlueprintAssignable)
	FOnHealed Delegate_OnHealed;

	UPROPERTY(BlueprintAssignable)
	FOnExperienceGained Delegate_OnExperienceGained;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Experience;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxExperience;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData FireDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData FrostDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Armour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Shield;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxShield;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MagicResist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ApplyDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ApplyFireDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ApplyFrostDamage;
	
public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Level);
	float GetLevel() const;
	void SetLevel(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Level);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MaxLevel);
	float GetMaxLevel() const;
	void SetMaxLevel(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxLevel);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Experience);
	float GetExperience() const;
	void SetExperience(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Experience);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MaxExperience);
	float GetMaxExperience() const;
	void SetMaxExperience(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxExperience);
	
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Health);
	float GetHealth() const;
	void SetHealth(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MaxHealth);
	float GetMaxHealth() const;
	void SetMaxHealth(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, BaseDamage);
	float GetBaseDamage() const;
	void SetBaseDamage(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(BaseDamage);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, WeaponDamage);
	float GetWeaponDamage() const;
	void SetWeaponDamage(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(WeaponDamage);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, FireDamage);
	float GetFireDamage() const;
	void SetFireDamage(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(FireDamage);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, FrostDamage);
	float GetFrostDamage() const;
	void SetFrostDamage(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(FrostDamage);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Armour);
	float GetArmour() const;
	void SetArmour(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Armour);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, Shield);
	float GetShield() const;
	void SetShield(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Shield);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MaxShield);
	float GetMaxShield() const;
	void SetMaxShield(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxShield);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, MagicResist);
	float GetMagicResist() const;
	void SetMagicResist(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MagicResist);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, ApplyDamage);
    float GetApplyDamage() const;
    void SetApplyDamage(float NewVal);
    GAMEPLAYATTRIBUTE_VALUE_INITTER(ApplyDamage);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, ApplyFireDamage);
	float GetApplyFireDamage() const;
	void SetApplyFireDamage(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(ApplyFireDamage);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAGAttributeSet, ApplyFrostDamage);
	float GetApplyFrostDamage() const;
	void SetApplyFrostDamage(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(ApplyFrostDamage);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
protected:
	virtual bool TryLevelUp();

	void HandleDamage(const FGameplayEffectModCallbackData& Data);
	
	void HandleHealing(const FGameplayEffectModCallbackData& Data);

	void HandleExperience(const FGameplayEffectModCallbackData& Data);
};
