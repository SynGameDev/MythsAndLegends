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

    UFUNCTION(BlueprintCallable)
    void SelectItem(class ABaseItem* SelectedItem);

    FORCEINLINE UWidget* GetSelectedItemWidget() const { return SelectedItemUI; }

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    class UWrapBox* SizeBoxList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    TSubclassOf<UUserWidget> SelectedItemUI_Class;
    UWidget* SelectedItemUI;
    bool IsInView = false;
    

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    TSubclassOf<UUserWidget> ItemButtonClass;
    UWidget* ItemButton;

    TArray<UWidget*> ItemButtonsInInventory;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Instanced", meta=(AllowPrivateAccess="true"))
    class ABaseItem* CurrentSelectedItem;
    
};
