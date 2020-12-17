// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/InventoryComponent.h"

#include "Characters/BaseCharacter.h"
#include "Characters/NPC.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "Controllers/BaseAIController.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "MythsAndLegends/Public/Items/BaseConsumable.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "Animation/AnimMontage.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CharacterAnimInstance.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentInventorySize = 0;
	InventoryMaxSize = 30;

}

void UInventoryComponent::DestroyItem(ABaseItem* Item)
{
	// Make sure that the item is valid before running the code
	if(!Item || !InventoryHasItem(Item))
		return;

	// Reduce the inventory size, remove the item from the inventory & destroy the item.
	CurrentInventorySize--;
	Inventory.Remove(Item);
	Item->Destroy();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// If we are spawning with a weapon in the world, pickup the weapon and then equip it.
	if(SpawnWithWeapon)
	{
		FActorSpawnParameters const SpawnInfo;
		if(auto* const SpawnedWeapon = GetWorld()->SpawnActor<ABaseWeapon>(ABaseWeapon::StaticClass(), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnInfo))
		{
			SpawnedWeapon->SpawnWeapon(WeaponToSpawn);
			PickupItem(Cast<ABaseItem>(SpawnedWeapon));
			EquipItem(Cast<ABaseItem>(SpawnedWeapon));
		}
	}
}

void UInventoryComponent::PickupItem(ABaseItem* Item)
{
	// if inventory is at max cap don't run this function
	// TODO: Display a message on screen
	if(CurrentInventorySize >= InventoryMaxSize)
		return;

	// If the inventory doesn't have this item than increment the inventory
	if(!InventoryHasItem(Item))
		CurrentInventorySize++;

	// Add the item to the inventory & attach it to the character
	Inventory.Add(Item);
	Item->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
	// Hide the Item
	Item->SetActorEnableCollision(false);
	Item->SetActorTickEnabled(false);
	Item->SetActorHiddenInGame(true);
}

void UInventoryComponent::DropItem(ABaseItem* Item)
{
	// TODO: Count item
	if(InventoryHasItem(Item))
	{
		// Remove the item from the inventory
		CurrentInventorySize--;
		Inventory.Remove(Item);
		// Create a new position for the item when dropped
		float const NewX = GetOwner()->GetActorLocation().X + FMath::RandRange(-15.0f, +15.0f);
		float const NewY = GetOwner()->GetActorLocation().Y + FMath::RandRange(-15.0f, +15.0f);
		// TODO: Get Ground location

		// Setup the item & display in world
		Item->SetActorLocation(FVector(NewX, NewY, GetOwner()->GetActorLocation().Z));
		Item->SetActorEnableCollision(true);
		Item->SetActorTickEnabled(true);
		Item->SetActorHiddenInGame(false);
		
	}
}



bool UInventoryComponent::InventoryHasItem(ABaseItem* Item) const
{
	// Loop though the inventory, if the item is found than return true otherwise false
	for (auto* Element : Inventory)
	{
		if(Element == Item)
			return true;

	}

	return false;
}

void UInventoryComponent::EquipItem(ABaseItem* const Item)
{
	// Make sure that the item is valid
	if(Item)
	{
		// Cast the item to check if it's a weapon
		if(auto* const Weapon = Cast<ABaseWeapon>(Item))
		{
			// Equip the item
			EquippedItem = Item;
			// Get the base character & make sure it's valid
			if(auto* const CharOwner = Cast<ABaseCharacter>(GetOwner()))
			{
				// Set the weapon mesh & set the attachment
				CharOwner->GetWeaponMesh()->SetStaticMesh(Item->GetItemMesh()->GetStaticMesh());
				CharOwner->GetWeaponMesh()->AttachToComponent(CharOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
                    Cast<ABaseWeapon>(Item)->GetSocketName());

				// Check if the owner character is a NPC if it is than set the attack cooldown
				if(auto* const NPC = Cast<ANPC>(CharOwner))
				{
					if(auto* const NPC_Controller = Cast<ABaseAIController>(CharOwner->GetController()))
					{
						NPC_Controller->GetBlackboardComponent()->SetValueAsFloat(NPC_Controller->AttackCooldown,
                            Cast<ABaseWeapon>(Item)->GetAttackCooldown());
					}
				}
			
			}
		} else if(auto* const Consumable = Cast<ABaseConsumable>(Item))
		{
			if(auto* const CharOwner = Cast<ABaseCharacter>(GetOwner()))
			{
				CharOwner->PlayAnimMontage(Consumable->GetAnimMontage());

				// Use the consumable
				Consumable->UseItem(CharOwner->GetSkillComponent());
				// Destroy the consumable
				DestroyItem(Item);
			}
		}
		
	} else
	{
		if(auto* const CharOwner = Cast<ABaseCharacter>(GetOwner()))
		{
			EquippedItem = nullptr;
			CharOwner->GetWeaponMesh()->SetStaticMesh(nullptr);
		}
	}
}




