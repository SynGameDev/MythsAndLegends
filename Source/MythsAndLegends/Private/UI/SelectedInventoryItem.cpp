// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/SelectedInventoryItem.h"
#include "MythsAndLegends/Public/UI/InventoryUI.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void USelectedInventoryItem::SetValues(FName const Name, FText const Desc)
{
    ItemName = Name;
    ItemDesc = Desc;
}

void USelectedInventoryItem::EquipItem()
{
    UE_LOG(LogTemp, Warning, TEXT("1"));
    if(auto* const PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(
        this, 0)))
    {
        UE_LOG(LogTemp, Warning, TEXT("2"));
        if(ABaseItem* const item = Cast<UInventoryUI>(InventoryWidget)->GetSelectedItem())
        {
            UE_LOG(LogTemp, Warning, TEXT("3"));
            if(auto* const Inv = PlayerChar->GetInventoryComponent())
            {
                UE_LOG(LogTemp, Warning, TEXT("4"));
                Inv->EquipItem(item);
            }
        }
    }
}

void USelectedInventoryItem::DropItem()
{
    if(auto* const PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(
        this, 0)))
    {
        if(ABaseItem* const item = Cast<UInventoryUI>(InventoryWidget)->GetSelectedItem())
        {
            if(auto* const Inv = PlayerChar->GetInventoryComponent())
            {
                if(Inv->GetEquippedWeapon() == item)
                {
                    Inv->DropItem(item);
                }
            }
        }
    }
}

