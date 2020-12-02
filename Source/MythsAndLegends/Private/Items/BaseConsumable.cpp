// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Items/BaseConsumable.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"

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
			// General Details
			ConsumingAnimation = ConsumableData->ConsumingAnimation;
			ConsumableTypes = ConsumableData->ConsumableTypes;
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

void ABaseConsumable::BeginPlay()
{
	Super::BeginPlay();
	if(SpawnInWorld)
	{
		SpawnWeapon();
	}

	SetupCommonDetails();
}

void ABaseConsumable::UseItem(USkillComponent* const CharacterSkillComponent)
{
	auto const ConsumableTypeLength = ConsumableTypes.Num();
	for(int i = 0; i < ConsumableTypeLength; i++)
	{
		switch(ConsumableTypes[i])
		{
			case Health:
				UseHealthPotion(CharacterSkillComponent);
				break;
			default:
				break;
		}
	}

}

void ABaseConsumable::UseHealthPotion(USkillComponent* const CharacterSkillComponent)
{
	if(!ConsumableTypes.Contains(Health))
		return;

	if(CharacterSkillComponent)
	{
		CharacterSkillComponent->AddHealth(HealthIncrement);
	}
}
