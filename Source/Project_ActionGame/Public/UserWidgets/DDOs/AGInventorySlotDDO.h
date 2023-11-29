// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "AGInventorySlotDDO.generated.h"

class UAGInventorySlotWidget;
/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGInventorySlotDDO : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UAGInventorySlotDDO();
	
public:
	UPROPERTY()
	UAGInventorySlotWidget* WidgetRef;

	FVector2D DragOffset;
};
