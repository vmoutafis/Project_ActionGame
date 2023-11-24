// Fill out your copyright notice in the Description page of Project Settings.


#include "AGGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGames/AGSaveGame.h"
#include "AGDataTypes.h"

UAGGameInstance::UAGGameInstance()
{
	SaveGame = nullptr;
}

bool UAGGameInstance::AddInventoryItem(FInventoryItem Item)
{
	if (!IsValid(SaveGame))
	{
		SaveGame = Cast<UAGSaveGame>(UGameplayStatics::CreateSaveGameObject(UAGSaveGame::StaticClass()));

		if (!IsValid(SaveGame))
			return false;
	}

	SaveGame->PlayerInventory.Add(Item);

	Delegate_OnItemAddedToInventory.Broadcast(Item);

	return true;
}
