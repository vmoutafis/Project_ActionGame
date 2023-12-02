// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "AGInventorySlotWidget.generated.h"

class UAGInventoryWidget;
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

	void SetSlot(UAGInventoryWidget* Widget, const FInventoryItem* NewItem, const int& Index);

	void SetAsEquipmentSlot(TEnumAsByte<EGearType> DefaultGearType);

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
protected:
	void UpdateSlot(const bool& bForceEmpty = false);

	void EnableHighlight(bool Enable);

	void EnableItemInfoWidget(bool Enabled);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Slot, meta=(BindWidget))
	UImage* IMG_Highlight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Slot, meta=(BindWidget))
	UImage* IMG_Border;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category=Slot, meta=(BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Slot|Colour")
	FLinearColor HighlightTint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Slot|Colour")
	FLinearColor NormalTint;
	
	FInventoryItem Item;

	int InventoryIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category="Slot|Colour")
	bool bDebugHighlight;

	UPROPERTY()
	UAGInventoryWidget* InventoryWidget;
};
