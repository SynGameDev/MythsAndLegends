#include "MythsAndLegends/Public/UI/QuickSlotWidget.h"

#include "Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"
#include "MythsAndLegends/Public/Items/BaseConsumable.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MythsAndLegends/Public/UI/MainHUD.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/UI/InventoryUI.h"

void UQuickSlotWidget::NativeConstruct()
{
	ItemSlot->OnClicked.AddDynamic(this, &UQuickSlotWidget::Action);
}

void UQuickSlotWidget::SelectItem()
{
	if(auto* const BaseCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		// Handle Equipping through the inventory
		BaseCharacter->GetInventoryComponent()->EquipItem(ItemInSlot);
		// If it's a consumable than remove it from the quick slot
		// TODO: Check if there is stacks of an item
		if(auto* const Consumable = Cast<ABaseConsumable>(ItemInSlot))
		{
			RemoveItem();
		}
	}
}

void UQuickSlotWidget::Action()
{
	// Validate the Main UI & player as the character
	if(auto* const Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if(auto* const MainHUD = Cast<UMainHUD>(Player->GetMainUI()))
		{
			// Check if the inventory is open
			if(auto* const Inventory = Cast<UInventoryUI>(MainHUD->GetInventoryWidget()))
			{
				SetItem(Inventory->GetSelectedItem());
			} else
			{
				SelectItem();	
			}
		}
	}
}


