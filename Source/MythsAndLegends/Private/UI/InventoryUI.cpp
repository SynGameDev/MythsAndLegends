// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/InventoryUI.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "MythsAndLegends/Public/UI/MainHUD.h"

#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Blueprint/WidgetTree.h"
#include "Components/WrapBox.h"
#include "UI/InventoryItemButton.h"
#include "Components/SizeBox.h"
#include "UI/SelectedInventoryItem.h"

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
                        Cast<UInventoryItemButton>(NewItem)->Setup(item, item->GetItemName());
                    }
                }
            }
        }
    }
}

void UInventoryUI::SelectItem(ABaseItem* SelectedItem)
{
    if(!SelectedItemUI_Class)
        return;
    
    if(auto* const PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        if(SelectedItem != CurrentSelectedItem)
        {
            CurrentSelectedItem = SelectedItem;
            if(SelectedItemUI == nullptr)
            {
                SelectedItemUI = WidgetTree->ConstructWidget<UWidget>(SelectedItemUI_Class);
                if(auto* main = Cast<UMainHUD>(PlayerChar->GetMainUI()))
                {
                    main->GetSelectedItemPoint()->AddChild(SelectedItemUI);
                }
            }
            if(auto* wid = Cast<USelectedInventoryItem>(SelectedItemUI))
            {
                wid->SetValues(SelectedItem->GetItemName(), SelectedItem->GetItemDesc());
                wid->InventoryWidget = this;
            }
        } else
        {
            Cast<UMainHUD>(PlayerChar->GetMainUI())->GetSelectedItemPoint()->RemoveChild(SelectedItemUI);
            SelectedItemUI = nullptr;
        }
    }
}

void UInventoryUI::CloseAllUI()
{
    CurrentSelectedItem = nullptr;
    
}

void UInventoryUI::NativeConstruct()
{
    GetInventoryItems();
}
