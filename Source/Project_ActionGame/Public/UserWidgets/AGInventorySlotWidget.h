// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "AGInventorySlotWidget.generated.h"

class UOverlay;
class UImage;

/**
 * 
 */
UCLASS()
class PROJECT_ACTIONGAME_API UAGInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAGInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

	void SetSlot(const FInventoryItem* NewItem);

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
	
protected:
	void UpdateSlot();

	void EnableHighlight(bool Enable);
	
protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Slot, meta=(BindWidget))
	UImage* IMG_Border;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Slot, meta=(BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Slot|Colour")
	FLinearColor HighlightTint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Slot|Colour")
	FLinearColor NormalTint;
	
	FInventoryItem Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Slot|Colour")
	bool bDebugHighlight;
};
