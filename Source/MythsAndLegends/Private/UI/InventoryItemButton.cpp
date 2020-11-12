// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/InventoryItemButton.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/UI/InventoryUI.h"
#include "MythsAndLegends/Public/UI/MainHUD.h"
#include "MythsAndLegends/Public/UI/SelectedInventoryItem.h"

#include "Kismet/GameplayStatics.h"
void UInventoryItemButton::ViewItem()
{
    if(auto* const PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        UE_LOG(LogTemp, Warning, TEXT("1"));
        if(auto* const Main = Cast<UMainHUD>(PlayerChar->GetMainUI()))
        {
            UE_LOG(LogTemp, Warning, TEXT("2"));
            if(auto* const Inv = Cast<UInventoryUI>(Main->GetInventoryWidget()))
            {
                UE_LOG(LogTemp, Warning, TEXT("3"));
                Inv->SelectItem(Item);
            }
        }
    } 
}
