#include "MythsAndLegends/Public/UI/QuickSlotWidget.h"

#include "Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"
#include "MythsAndLegends/Public/Items/BaseConsumable.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

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

void UQuickSlotWidget::ShowAvailableSlot()
{
	ItemSlot->
}

