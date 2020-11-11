// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/InventoryUI.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"

#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Blueprint/WidgetTree.h"
#include "Components/WrapBox.h"
void UInventoryUI::GetInventoryItems()
{
    if(!ItemButtonClass)
        return;

    if(APlayerCharacter* const PlayerChar =
        Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        if(auto* Inventory = PlayerChar->GetInventoryComponent())
        {
            TArray<ABaseItem*> InvItems = Inventory->GetInventoryItems();
            for(auto* item : InvItems)
            {
                if(item)
                {
                    UWidget* NewItem = WidgetTree->ConstructWidget<UWidget>(ItemButtonClass);
                    if(NewItem)
                    {
                        ItemButtonsInInventory.Add(NewItem);
                        SizeBoxList->AddChild(NewItem);
                    }
                }
            }
        }
    }
}
