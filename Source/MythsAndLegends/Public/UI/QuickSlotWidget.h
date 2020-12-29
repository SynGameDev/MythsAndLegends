﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotWidget.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	void SelectItem();
	FORCEINLINE void SetItem(class ABaseItem* Item) { ItemInSlot = Item; }
	FORCEINLINE void RemoveItem() { ItemInSlot=nullptr;}
	// Set Select Slot
	void ShowAvailableSlot();
private:
	class ABaseItem* ItemInSlot;
	bool bIsSlotAvailable;

	// --- UI Items --- //
	UPROPERTY(meta=(BindWidgetOptional))
	class UButton* ItemSlot;
	UPROPERTY(meta=(BindWidgetOptional))
	class UImage* ItemIcon;
};