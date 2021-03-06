// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/InventoryComponent.h"

#include "Characters/BaseCharacter.h"
#include "Characters/NPC.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Controllers/BaseAIController.h"
#include "UMG/Public/Blueprint/UserWidget.h"

#include "BehaviorTree/BlackboardComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentInventorySize = 0;
	InventoryMaxSize = 30;

}

void UInventoryComponent::PickupItem(ABaseItem* Item)
{
	if(CurrentInventorySize >= InventoryMaxSize)
		return;

	if(!InventoryHasItem(Item))
		CurrentInventorySize++;

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
		CurrentInventorySize--;
		Inventory.Remove(Item);

		float const NewX = GetOwner()->GetActorLocation().X + FMath::RandRange(-15.0f, +15.0f);
		float const NewY = GetOwner()->GetActorLocation().Y + FMath::RandRange(-15.0f, +15.0f);
		// TODO: Get Ground location

		Item->SetActorLocation(FVector(NewX, NewY, GetOwner()->GetActorLocation().Z));
		Item->SetActorEnableCollision(true);
		Item->SetActorTickEnabled(true);
		Item->SetActorHiddenInGame(false);
		
	}
}

bool UInventoryComponent::InventoryHasItem(ABaseItem* Item) const
{
	for (auto* Element : Inventory)
	{
		if(Element == Item)
			return true;

	}

	return false;
}

void UInventoryComponent::EquipItem(ABaseItem* const Item)
{
	// TODO: Check that item is equipable
	if(Item)
	{
		EquippedItem = Item;
		if(auto* const CharOwner = Cast<ABaseCharacter>(GetOwner()))
		{
			CharOwner->GetWeaponMesh()->SetStaticMesh(Item->GetItemMesh()->GetStaticMesh());
			CharOwner->GetWeaponMesh()->AttachToComponent(CharOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
				Cast<ABaseWeapon>(Item)->GetSocketName());

			if(auto* const NPC = Cast<ANPC>(CharOwner))
			{
				if(auto* const NPC_Controller = Cast<ABaseAIController>(CharOwner->GetController()))
				{
					NPC_Controller->GetBlackboardComponent()->SetValueAsFloat(NPC_Controller->AttackCooldown,
						Cast<ABaseWeapon>(Item)->GetAttackCooldown());
				}
			}
		}
	}
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if(SpawnWithWeapon && EquippedItem)
	{
		EquipItem(EquippedItem);
	}
}





