// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/MainHUD.h"
#include "Components/SizeBox.h"
#include "UMG/Public/Blueprint/WidgetTree.h"

UMainHUD::UMainHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    
}

void UMainHUD::OpenInventory(APlayerController* Controller)
{
    UE_LOG(LogTemp, Warning, TEXT("Validating"));
    if(!InventoryWidgetClass && InventoryContainer)
        return;

    UE_LOG(LogTemp, Warning, TEXT("Toggling"))

    IsInventoryOpen = !IsInventoryOpen;
    if(IsInventoryOpen)
    {
        UE_LOG(LogTemp, Warning, TEXT("Opened"));
        InventoryWidget = WidgetTree->ConstructWidget<UWidget>(InventoryWidgetClass);
        InventoryContainer->AddChild(InventoryWidget);
    } else
    {
        InventoryContainer->RemoveChild(InventoryWidget);
        InventoryWidget = nullptr;
    }
}
