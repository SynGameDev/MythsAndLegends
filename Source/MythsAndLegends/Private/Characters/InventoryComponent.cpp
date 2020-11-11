// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"

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



