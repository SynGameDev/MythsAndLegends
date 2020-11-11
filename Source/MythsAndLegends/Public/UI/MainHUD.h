// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
public:

    UMainHUD(const FObjectInitializer& ObjectInitializer);
    
    UFUNCTION(BlueprintCallable)
    void OpenInventory(class APlayerController* Controller);
    
private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    class USizeBox* InventoryContainer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|Variables", meta=(AllowPrivateAccess="true"))
    bool IsInventoryOpen = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Variables", meta=(AllowPrivateAccess="true"))
    TSubclassOf<UUserWidget> InventoryWidgetClass;
    class UWidget* InventoryWidget;
    
};