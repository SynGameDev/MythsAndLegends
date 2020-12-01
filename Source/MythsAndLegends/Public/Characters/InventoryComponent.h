// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTHSANDLEGENDS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void PickupItem(class ABaseItem* Item);
	void DropItem(class ABaseItem* Item);
	bool InventoryHasItem(class ABaseItem* Item) const;

	void EquipItem(class ABaseItem* const Item);

	FORCEINLINE TArray<class ABaseItem*> GetInventoryItems() const { return Inventory; }
	FORCEINLINE class ABaseItem* GetEquippedWeapon() const { UE_LOG(LogTemp, Warning, TEXT("GettingWeapon")); return EquippedItem; }

	void DestroyItem(class ABaseItem* Item);

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<class ABaseItem*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Initial Settings", meta=(AllowPrivateAccess="true"))
	int32 InventoryMaxSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Initial Settings", meta=(AllowPrivateAccess="true"))
	int32 CurrentInventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning|Weapon", meta=(AllowPrivateAccess="true"))
	bool SpawnWithWeapon;
	/* ID of the weapon we want to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning|Weapon", meta=(AllowPrivateAccess="true", EditCondition="SpawnWithWeapon"))
	FName WeaponToSpawn;

	// --- IN HAND --- //
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	class ABaseItem* EquippedItem;	
		
};
