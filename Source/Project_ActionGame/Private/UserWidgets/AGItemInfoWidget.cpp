// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/AGItemInfoWidget.h"

UAGItemInfoWidget::UAGItemInfoWidget()
{
}

void UAGItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UAGItemInfoWidget::SetItem(const FInventoryItem& NewItem)
{
	Item = NewItem;
}
