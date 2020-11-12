// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemButton.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UInventoryItemButton : public UUserWidget
{
	GENERATED_BODY()
public:
    
    FORCEINLINE void Setup(class ABaseItem* lItem, FName lItemName) { Item = lItem; ItemName = lItemName; }
    FName GetItemName() const { return ItemName; }

    UFUNCTION(BlueprintCallable)
    void ViewItem();
    
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
    class ABaseItem* Item;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
    FName ItemName;
};
