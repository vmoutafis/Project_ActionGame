// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGPlayerHUDWidget.h"

#include "AGDataTypes.h"
#include "AGGameInstance.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/ScrollBox.h"
#include "Loot/AGLoot.h"
#include "UserWidgets/AGItemCollectWidget.h"

UAGPlayerHUDWidget::UAGPlayerHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SB_ItemCollect = nullptr;
	TempCollectItemsSet = false;
}

void UAGPlayerHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsDesignTime() && IsValid(ItemCollectWidgetClass))
	{
		SB_ItemCollect->ClearChildren();
		
		for (uint8 i = 0; i < 6; ++i)
		{
			UAGItemCollectWidget* NewWidget = CreateWidget<UAGItemCollectWidget>(GetWorld(), ItemCollectWidgetClass);

			NewWidget->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 2.0f));
			SB_ItemCollect->AddChild(NewWidget);

			TempCollectItemsSet = true;
		}
	}
	else
	{
		if (TempCollectItemsSet)
			SB_ItemCollect->ClearChildren();
	}

	if (IsValid(SB_ItemCollect))
		SB_ItemCollect->SetScrollWhenFocusChanges(EScrollWhenFocusChanges::AnimatedScroll);
}

void UAGPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Cast<UAGGameInstance>(GetGameInstance())->Delegate_LootCollected.AddDynamic(this, &UAGPlayerHUDWidget::CollectItem);
}

void UAGPlayerHUDWidget::CollectItem(FInventoryItem Item)
{
	CollectedItems.Add(std::move(Item));

	if (!GetWorld()->GetTimerManager().IsTimerActive(TH_AddItemToCollected))
		GetWorld()->GetTimerManager().SetTimer(TH_AddItemToCollected, this, &UAGPlayerHUDWidget::AddItemToCollected, 0.1f, true);
}

void UAGPlayerHUDWidget::AddItemToCollected()
{
	if (CollectedItems.Num() <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_AddItemToCollected);
		return;
	}
	
	UAGItemCollectWidget* NewWidget = CreateWidget<UAGItemCollectWidget>(GetOwningPlayer(), ItemCollectWidgetClass);

	const AAGLoot* ItemObj = CollectedItems[0].LootClass.GetDefaultObject();
	const FInventoryItem ItemLoot = CollectedItems[0];
	NewWidget->InitialiseItem(ItemObj->DisplayName, ItemObj->Icon, ItemLoot.Rarity);
	NewWidget->SetIsFocusable(true);
	NewWidget->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 2.0f));
	SB_ItemCollect->AddChild(NewWidget);
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(TH_ScrollNextCollectedItem))
		GetWorld()->GetTimerManager().SetTimer(TH_ScrollNextCollectedItem, this, &UAGPlayerHUDWidget::ScrollNextCollectedItem, 2.0f);

	CollectedItems.RemoveAt(0);
}

void UAGPlayerHUDWidget::RemoveCollectedItem()
{
	SB_ItemCollect->GetChildAt(0)->RemoveFromParent();
}

void UAGPlayerHUDWidget::ScrollNextCollectedItem()
{
	if (SB_ItemCollect->GetChildrenCount() <= 0)
		return;

	Cast<UAGItemCollectWidget>(SB_ItemCollect->GetChildAt(0))->PlayDisappearAnim();

	GetWorld()->GetTimerManager().SetTimer(TH_ScrollNextCollectedItem, this, &UAGPlayerHUDWidget::ScrollNextCollectedItem, 2.0f);
	
	GetWorld()->GetTimerManager().SetTimer(TH_RemoveCollectedItem, this, &UAGPlayerHUDWidget::RemoveCollectedItem, 1.0f);
}
