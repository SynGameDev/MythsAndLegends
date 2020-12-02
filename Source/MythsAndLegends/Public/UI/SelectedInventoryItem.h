// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectedInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API USelectedInventoryItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details")
	FText ItemDesc;

	UWidget* InventoryWidget;

	UFUNCTION(BlueprintCallable)
	void SetValues(FName const Name, FText const Desc);

	UFUNCTION(BlueprintCallable)
	void EquipItem();

	UFUNCTION(BlueprintCallable)
	void DropItem();

protected:
	UPROPERTY(meta=(BindWidget))
	class UImage* BackgroundImage;
	UPROPERTY(meta=(BindWidget))
	class UImage* ItemIcon;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemNameBlock;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemDescription;
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* ButtonContainer;
	UPROPERTY(meta=(BindWidget))
	class UButton* ActionButton;
	UPROPERTY(meta=(BindWidget))
	class Ubutton* DropButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* QuickSlotButton;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ActionText;
	
};
