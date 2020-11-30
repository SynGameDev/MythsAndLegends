// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Items/BaseConsumable.h"

ABaseConsumable::ABaseConsumable()
{
	SpawnInWorld = true;
}

void ABaseConsumable::SpawnWeapon()
{
	static const FString ContextString = "Consumable Table Context";
	FString ConsumableID = "";
	TArray<FName> ItemNames = ConsumableDataTable->GetRowNames();

	if(SpawnItemID == "")
	{
		SpawnItemID = ItemNames[FMath::RandRange(0, ItemNames.Num() - 1)];
	}

	FConsumableDataTable* const ConsumableData = ConsumableDataTable->FindRow<FConsumableDataTable>(SpawnItemID, ContextString, true);
	if(ConsumableData)
	{
		static const FString ItemDataContextString = "item Table Context";
		FItemDataTable* ItemData = ItemDataTable->FindRow<FItemDataTable>(SpawnItemID, ItemDataContextString, true);
		if(ItemData)
		{
			// --- BASE DETAILS --- //
			ItemName = ItemData->ItemName;
			ItemDescription = ItemData->ItemDescription;
			ItemTier = ItemData->ItemTier;
			ItemMesh->SetStaticMesh(ItemData->ItemMesh);
			MeshOutline->SetStaticMesh(ItemData->ItemMesh);
			MeshOutline->SetMaterial(0, ItemData->OutlineMaterial);
			ItemImage = ItemData->ItemIcon;
			// --- CONSUMABLE DETAILS --- //
			ConsumingAnimation = ConsumableData->ConsumingAnimation;
			
			// Health Details
			IsHealthConsumable = ConsumableData->IsHealthConsumable;
			HealthIncrement = ConsumableData->HealthIncrement;
			DefenceIncrement = ConsumableData->DefenceIncrement;

		}
	}
}

void ABaseConsumable::SpawnWeapon(bool Spawn)
{
	SpawnInWorld = Spawn;
	SpawnWeapon();
}

void ABaseConsumable::SpawnWeapon(FName WeaponName)
{
	SpawnItemID = WeaponName;
	SpawnWeapon();
}

void ABaseConsumable::SpawnWeapon(FName WeaponName, bool Spawn)
{
	SpawnInWorld = Spawn;
	SpawnItemID = WeaponName;
	SpawnWeapon();
}
