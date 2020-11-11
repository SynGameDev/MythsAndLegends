// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void GetInventoryItems();


private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    class UWrapBox* SizeBoxList;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    TSubclassOf<UUserWidget> ItemButtonClass;
    UWidget* ItemButton;

    TArray<UWidget*> ItemButtonsInInventory;
};
