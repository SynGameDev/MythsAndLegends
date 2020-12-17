// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/SelectedInventoryItem.h"
#include "MythsAndLegends/Public/UI/InventoryUI.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USelectedInventoryItem::SetValues(FName const Name, FText const Desc, ABaseItem* const Item)
{
    // Setup the text widgets of the selected item
    ItemNameBlock->SetText(FText::FromName(Name));
    ItemDescription->SetText(Desc);

    // Cast to the base character in order to check if this item is equipped or not,
    // than set the values based on the result.
    if(auto* const PlayChar = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        if(PlayChar->GetInventoryComponent()->GetEquippedWeapon() == Item)
        {
            ActionText->SetText(FText::AsCultureInvariant("Unequip"));
            IsEquipped = true;
        } else
        {
            ActionText->SetText(FText::AsCultureInvariant("Equip"));
            IsEquipped = false;
        }
    }

}

void USelectedInventoryItem::EquipItem()
{
    // Cast to the player character& make sure that it's valid
    if(auto* const PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(
        this, 0)))
    {
        // Get the current selected selected item and make sure it's valid
        if(ABaseItem* const item = Cast<UInventoryUI>(InventoryWidget)->GetSelectedItem())
        {
           // Cast to the inventory and make sure it's valid
            if(auto* const Inv = PlayerChar->GetInventoryComponent())
            {
                // Check whether the item is equipped or not and complete the required action
                if(IsEquipped)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Equipping"));
                    Inv->EquipItem(nullptr);
                    IsEquipped = false;
                    ActionText->SetText(FText::AsCultureInvariant("Equip"));
                } else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Unequipping"));
                    Inv->EquipItem(item);
                    ActionText->SetText(FText::AsCultureInvariant("Unequip"));
                    IsEquipped = true;
                }
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

    Cast<UInventoryUI>(InventoryWidget)->ClearInventory();
    Cast<UInventoryUI>(InventoryWidget)->GetInventoryItems();
}

void USelectedInventoryItem::NativeConstruct()
{
    Super::NativeConstruct();

    if(!ActionButton->OnClicked.IsBound())
        ActionButton->OnClicked.AddDynamic(this, &USelectedInventoryItem::EquipItem);

    if(!DropButton->OnClicked.IsBound())
        DropButton->OnClicked.AddDynamic(this, &USelectedInventoryItem::DropItem);
}

