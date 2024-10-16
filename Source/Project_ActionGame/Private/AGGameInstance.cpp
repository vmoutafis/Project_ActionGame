// Fill out your copyright notice in the Description page of Project Settings.


#include "AGGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGames/AGSaveGame.h"
#include "AGDataTypes.h"
#include "Characters/AGPlayerCharacter.h"

UAGGameInstance::UAGGameInstance()
{
	SaveGame = nullptr;
	MaxInventorySlots = 25;
}

bool UAGGameInstance::CollectLoot(const FInventoryItem& Item)
{
	const bool Result = AddInventoryItem(Item);

	if (Result)
		Delegate_LootCollected.Broadcast(Item);

	return Result;
}

bool UAGGameInstance::AddInventoryItem(const FInventoryItem& Item)
{
	if (GetInventory().Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No inventory exists."))
		return false;
	}

	const bool Result = SaveGame->AddItemToInventory(Item);

	if (Result)
		Delegate_InventoryUpdated.Broadcast();

	return Result;
}

void UAGGameInstance::SwapInventoryItems(const int& ItemIndex1, const int& ItemIndex2)
{
	if (!IsValid(CreateSaveGameObject()))
		return;

	SaveGame->SwapInventoryItems(ItemIndex1, ItemIndex2);

	Delegate_InventoryUpdated.Broadcast();
}

bool UAGGameInstance::UnEquipToInventory(TEnumAsByte<EEquipmentSlots> EquipSlot, const int& InventorySlot)
{
	if (!IsValid(CreateSaveGameObject()))
		return false;

	const bool Result = SaveGame->UnEquipToInventory(EquipSlot, InventorySlot);

	if (Result)
		Delegate_InventoryUpdated.Broadcast();
	
	return Result;
}

int UAGGameInstance::GetNumInventoryItems()
{
	if (!IsValid(CreateSaveGameObject()))
		return 0;

	return SaveGame->PlayerInventory.Num();
}

TArray<FInventoryItem> UAGGameInstance::GetInventory()
{
	if (!CreateSaveGameObject())
		return TArray<FInventoryItem>();

	if (SaveGame->PlayerInventory.Num() != MaxInventorySlots)
		SaveGame->PlayerInventory.SetNum(MaxInventorySlots);
		
	return SaveGame->PlayerInventory;
}

TArray<FInventoryItem> UAGGameInstance::GetAllEquipment()
{
	if (!CreateSaveGameObject())
		return TArray<FInventoryItem>();
		
	return SaveGame->PlayerEquipment;
}

FInventoryItem UAGGameInstance::GetEquipmentBySlot(TEnumAsByte<EEquipmentSlots> Slot)
{
	if (!CreateSaveGameObject())
		return FInventoryItem();
		
	return SaveGame->GetEquipmentItem(Slot);
}

bool UAGGameInstance::ActivateInventoryItem(const int& Index, TEnumAsByte<EEquipmentSlots> Slot)
{
	if (!CreateSaveGameObject())
		return false;

	const bool Result = SaveGame->ActivateInventoryItem(Index, Slot);

	if (Result)
		Delegate_InventoryUpdated.Broadcast();
	
	return Result;
}

bool UAGGameInstance::SwapEquippedWeapons()
{
	if (!CreateSaveGameObject())
		return false;

	SaveGame->SwapEquippedWeapons();

	Delegate_InventoryUpdated.Broadcast();

	return true;
}

UAGSaveGame* UAGGameInstance::CreateSaveGameObject(const bool& ForceNew)
{
	if (IsValid(SaveGame) && !ForceNew)
		return SaveGame;
	
	SaveGame = Cast<UAGSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));

	SaveGame->Delegate_EquipmentUpdated.AddDynamic(this, &UAGGameInstance::EquipmentUpdated);
	
	return SaveGame;
}

void UAGGameInstance::EquipmentUpdated(TEnumAsByte<EEquipmentSlots> Slot)
{
	if (AAGPlayerCharacter* PlayerRef = Cast<AAGPlayerCharacter>(GetPrimaryPlayerController()->GetPawn()))
	{
		if (Slot == ES_Weapon)
		{
			const FInventoryItem Item = GetEquipmentBySlot(Slot);
			const FInventoryItem* ItemObj = nullptr;

			if (!Item.bIsEmpty)
				ItemObj = &Item;
			
			PlayerRef->EquipWeapon(ItemObj);
		}
	}
}
