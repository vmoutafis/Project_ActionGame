// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGPlayerHUDWidget.h"

#include "AGDataTypes.h"
#include "AGGameInstance.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/ScrollBox.h"
#include "Loot/AGLoot.h"
#include "UserWidgets/AGItemCollectWidget.h"

void UAGPlayerHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsDesignTime() && IsValid(ItemCollectWidgetClass))
	{
		for (uint8 i = 0; i < 6; ++i)
		{
			UAGItemCollectWidget* NewWidget = CreateWidget<UAGItemCollectWidget>(GetWorld(), ItemCollectWidgetClass);

			NewWidget->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 2.0f));
			SB_ItemCollect->AddChild(NewWidget);
		}
	}
	else
	{
		SB_ItemCollect->ClearChildren();
	}
}

void UAGPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UAGGameInstance* GI = Cast<UAGGameInstance>(GetGameInstance());

	if (!IsValid(GI))
		return;

	GI->Delegate_OnItemAddedToInventory.AddDynamic(this, &UAGPlayerHUDWidget::OnItemAddedToInventory_Pure);
}

void UAGPlayerHUDWidget::CollectItem(FInventoryItem Item)
{
	UAGItemCollectWidget* NewWidget = CreateWidget<UAGItemCollectWidget>(GetOwningPlayer(), ItemCollectWidgetClass);

	const AAGLoot* ItemObj = Item.LootClass.GetDefaultObject();
	NewWidget->InitialiseItem(ItemObj->DisplayName, ItemObj->Icon, ItemObj->Rarity);

	NewWidget->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 2.0f));
	SB_ItemCollect->AddChild(NewWidget);
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(TH_ScrollNextCollectedItem))
		GetWorld()->GetTimerManager().SetTimer(TH_ScrollNextCollectedItem, this, &UAGPlayerHUDWidget::ScrollNextCollectedItem, 2.0f);
}

void UAGPlayerHUDWidget::RemoveCollectedItem()
{
	SB_ItemCollect->GetChildAt(0)->RemoveFromParent();
}

void UAGPlayerHUDWidget::ScrollNextCollectedItem()
{
	if (SB_ItemCollect->GetChildrenCount() <= 0)
		return;

	if (SB_ItemCollect->GetChildrenCount() > 1)
	{
		SB_ItemCollect->GetChildAt(1)->SetFocus();
		GetWorld()->GetTimerManager().SetTimer(TH_ScrollNextCollectedItem, this, &UAGPlayerHUDWidget::ScrollNextCollectedItem, 2.0f);
	}
	
	GetWorld()->GetTimerManager().SetTimer(TH_RemoveCollectedItem, this, &UAGPlayerHUDWidget::RemoveCollectedItem, 1.0f);
}

void UAGPlayerHUDWidget::OnItemAddedToInventory_Pure(FInventoryItem Item)
{
	CollectItem(std::move(Item));
	
	OnItemAddedToInventory(std::move(Item));
	UE_LOG(LogTemp, Warning, TEXT("Item Added: %s"), *Item.LootClass->GetName());
}
