// Fill out your copyright notice in the Description page of Project Settings.


#include "AGGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGames/AGSaveGame.h"
#include "AGDataTypes.h"

UAGGameInstance::UAGGameInstance()
{
	SaveGame = nullptr;
	MaxInventorySlots = 25;
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
		Delegate_OnItemAddedToInventory.Broadcast(Item);

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

FInventoryItem UAGGameInstance::GetEquipmentByType(TEnumAsByte<EGearType> GearType)
{
	if (!CreateSaveGameObject())
		return FInventoryItem();
		
	return SaveGame->GetEquipmentItem(GearType);
}

bool UAGGameInstance::ActivateInventoryItem(const int& Index)
{
	if (!CreateSaveGameObject())
		return false;
	
	return SaveGame->ActivateInventoryItem(Index);
}

UAGSaveGame* UAGGameInstance::CreateSaveGameObject(const bool& ForceNew)
{
	if (IsValid(SaveGame) && !ForceNew)
		return SaveGame;
	
	return SaveGame = Cast<UAGSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
}
