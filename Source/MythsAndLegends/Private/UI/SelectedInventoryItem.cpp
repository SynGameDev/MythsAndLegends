// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/SelectedInventoryItem.h"
#include "MythsAndLegends/Public/UI/InventoryUI.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
void USelectedInventoryItem::SetValues(FName const Name, FText const Desc)
{
    ItemNameBlock->SetText(FText::FromName(Name));
    ItemDescription->SetText(Desc);
    

    
}

void USelectedInventoryItem::EquipItem()
{
    
    if(auto* const PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(
        this, 0)))
    {
        
        if(ABaseItem* const item = Cast<UInventoryUI>(InventoryWidget)->GetSelectedItem())
        {
           
            if(auto* const Inv = PlayerChar->GetInventoryComponent())
            {
                
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

