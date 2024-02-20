// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGInventoryWidget.h"

#include "AGDataTypes.h"
#include "AGGameInstance.h"
#include "AGHelperFunctions.h"
#include "Characters/AGCharacter.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "UserWidgets/AGInventorySlotWidget.h"
#include "UserWidgets/AGItemInfoWidget.h"
#include "Weapons/AGWeapon.h"
#include "AbilitySystem/AGAbilitySystemComponent.h"
#include "AbilitySystem/AGAttributeSet.h"
#include "Components/TextBlock.h"
#include "UserWidgets/AGStatIconWidget.h"
#include "UserWidgets/AGStatWidget.h"

UAGInventoryWidget::UAGInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SB_Inventory= nullptr;
	UGP_Inventory = nullptr;
	DesignTimeLootClass = AAGWeapon::StaticClass();
	InventorySlotClass = nullptr;
	DebugInventoryMaxSlots = 50;
	ISW_Head = nullptr;
	ISW_Neck = nullptr;
	ISW_UpperBody = nullptr;
	ISW_Hands = nullptr;
	ISW_Ring = nullptr;
	ISW_Legs = nullptr;
	ISW_Feet = nullptr;
	ISW_Weapon = nullptr;
	ISW_SecondaryWeapon = nullptr;
	IIW_ItemInfo = nullptr;
	AbilitySystemComponent = nullptr;
	STAT_MaxHealth = nullptr;
	STAT_Armour = nullptr;
	STAT_Damage = nullptr;
	TXT_Level = nullptr;
	STATICO_FireDamage = nullptr;
	STATICO_FrostDamage = nullptr;
	STAT_MagicResist = nullptr;
	STAT_MaxShield = nullptr;
	LevelText = "LEVEL";
}

void UAGInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!IsValid(UGP_Inventory) || !IsValid(InventorySlotClass))
		return;

	UGP_Inventory->ClearChildren();

	int Row = 0;
	int Column = 0;

	for (int i = 0; i < DebugInventoryMaxSlots; ++i)
	{
		UAGInventorySlotWidget* NewWidget = CreateWidget<UAGInventorySlotWidget>(GetWorld(), InventorySlotClass);
		
		if (i < 5 && IsDesignTime())
		{
			FInventoryItem Item = FInventoryItem(DesignTimeLootClass, UAGHelperFunctions::GetRandomRarity());
			NewWidget->SetSlot(this, &Item, i);
		}

		UGP_Inventory->AddChildToUniformGrid(NewWidget, Row, Column);

		if (Column > 2)
		{
			Column = 0;
			Row++;
		}
		else
			Column++;
	}
}

void UAGInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateInventory();

	Cast<UAGGameInstance>(GetGameInstance())->Delegate_InventoryUpdated.AddDynamic(this, &UAGInventoryWidget::UpdateInventory);

	InitialiseAbilitySystem();
}

void UAGInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();

	Cast<UAGGameInstance>(GetGameInstance())->Delegate_InventoryUpdated.Clear();

	GetWorld()->GetTimerManager().ClearTimer(TH_InitAbilitySystem);
	
	AbilitySystemComponent->Delegate_OnAnyStatChanged.Clear();
}

void UAGInventoryWidget::EnableItemInfoWidget(const FInventoryItem& Item, UAGInventorySlotWidget* SlotWidget)
{
	if (!IsValid(IIW_ItemInfo))
		return;
	
	if (Item.bIsEmpty)
	{
		IIW_ItemInfo->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	IIW_ItemInfo->SetItem(Item);
	IIW_ItemInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

TArray<UAGInventorySlotWidget*> UAGInventoryWidget::GetAllEquipmentSlots() const
{
	return {
		ISW_Head,
		ISW_Neck,
		ISW_UpperBody,
		ISW_Hands,
		ISW_Ring,
		ISW_Legs,
		ISW_Feet,
		ISW_Weapon,
		ISW_SecondaryWeapon
	};
}

void UAGInventoryWidget::UpdateInventory()
{
	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(UGP_Inventory) || !IsValid(InventorySlotClass) || !IsValid(GI))
		return;
	
	UGP_Inventory->ClearChildren();
	
	int Row = 0;
	int Column = 0;
	
	for (int i = 0; i < GI->GetInventory().Num(); ++i)
	{
		UAGInventorySlotWidget* NewWidget = CreateWidget<UAGInventorySlotWidget>(GetWorld(), InventorySlotClass);

		NewWidget->SetSlot(this, &GI->GetInventory()[i], i);

		UGP_Inventory->AddChildToUniformGrid(NewWidget, Row, Column);

		if (Column > 2)
		{
			Column = 0;
			Row++;
		}
		else
			Column++;
	}

	for (int32 i = 0; i < GetAllEquipmentSlots().Num(); ++i)
	{
		GetAllEquipmentSlots()[i]->SetSlot(this, &GI->GetAllEquipment()[i], i);
		GetAllEquipmentSlots()[i]->SetAsEquipmentSlot(static_cast<TEnumAsByte<EEquipmentSlots>>(i));
	}
}

void UAGInventoryWidget::InitialiseAbilitySystem()
{ 
	if (IsValid(AbilitySystemComponent))
	{
		OnAbilitySystemInit();
		return;
	}
	
	const AAGCharacter* CharRef = Cast<AAGCharacter>(GetOwningPlayer()->GetPawn());
	
	if (!IsValid(CharRef))
	{
		GetWorld()->GetTimerManager().SetTimer(TH_InitAbilitySystem, this, &UAGInventoryWidget::InitialiseAbilitySystem, 0.1f);
		return;
	}

	AbilitySystemComponent = Cast<UAGAbilitySystemComponent>(CharRef->GetAbilitySystemComponent());

	if (!IsValid(AbilitySystemComponent))
	{
		GetWorld()->GetTimerManager().SetTimer(TH_InitAbilitySystem, this, &UAGInventoryWidget::InitialiseAbilitySystem, 0.1f);
		return;
	}

	OnAbilitySystemInit();
}

void UAGInventoryWidget::OnAbilitySystemInit()
{
	AbilitySystemComponent->Delegate_OnAnyStatChanged.AddDynamic(this, &UAGInventoryWidget::OnStatChange);

	UpdateAllStats();
}

void UAGInventoryWidget::OnStatChange(const FGameplayAttribute& Attribute, float Value)
{
	const UAGAttributeSet* AttribSet = AbilitySystemComponent->GetOwnerAttributes();

	if (!IsValid(AttribSet))
		return;

	if (Attribute == AttribSet->GetMaxHealthAttribute())
		STAT_MaxHealth->SetValue(Value);

	if (Attribute == AttribSet->GetMaxShieldAttribute())
		STAT_MaxShield->SetValue(Value);

	if (Attribute == AttribSet->GetBaseDamageAttribute() ||
		Attribute == AttribSet->GetWeaponDamageAttribute())
	{
		SetDamageText(Attribute, Value);
	}

	if (Attribute == AttribSet->GetArmourAttribute())
		STAT_Armour->SetValue(Value);

	if (Attribute == AttribSet->GetLevelAttribute())
		SetLevelText(Value);

	if (Attribute == AttribSet->GetMagicResistAttribute())
		STAT_MagicResist->SetValue(Value);

	if (Attribute == AttribSet->GetFireDamageAttribute())
		STATICO_FireDamage->SetValue(AttribSet->GetFireDamage());

	if (Attribute == AttribSet->GetFrostDamageAttribute())
		STATICO_FrostDamage->SetValue(AttribSet->GetFrostDamage());
}

void UAGInventoryWidget::SetDamageText(const FGameplayAttribute& Attribute, float Value)
{
	const UAGAttributeSet* AttribSet = AbilitySystemComponent->GetOwnerAttributes();

	if (!IsValid(AttribSet))
		return;

	if (Attribute == AttribSet->GetBaseDamageAttribute())
		Value += AttribSet->GetWeaponDamage();

	if (Attribute == AttribSet->GetWeaponDamageAttribute())
		Value += AttribSet->GetBaseDamage();

	STAT_Damage->SetValue(Value);
}

void UAGInventoryWidget::SetLevelText(float Value)
{
	TXT_Level->SetText(FText::FromString(LevelText + FString(" ") + FString::FromInt(FMath::TruncToInt(Value))));
}

void UAGInventoryWidget::UpdateAllStats()
{
	const UAGAttributeSet* AttribSet = AbilitySystemComponent->GetOwnerAttributes();

	if (!IsValid(AttribSet))
		return;

	STAT_MaxHealth->SetValue(AttribSet->GetMaxHealth());

	STAT_MaxShield->SetValue(AttribSet->GetMaxShield());

	SetDamageText(AttribSet->GetBaseDamageAttribute(), AttribSet->GetBaseDamage());

	STAT_Armour->SetValue(AttribSet->GetArmour());

	SetLevelText(AttribSet->GetLevel());

	STAT_MagicResist->SetValue(AttribSet->GetMagicResist());

	STATICO_FireDamage->SetValue(AttribSet->GetFireDamage());
	
	STATICO_FrostDamage->SetValue(AttribSet->GetFrostDamage());
}
