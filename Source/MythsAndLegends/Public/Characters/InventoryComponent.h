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

	FORCEINLINE TArray<class ABaseItem*> GetInventoryItems() const { return Inventory; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<class ABaseItem*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Initial Settings", meta=(AllowPrivateAccess="true"))
	int32 InventoryMaxSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Initial Settings", meta=(AllowPrivateAccess="true"))
	int32 CurrentInventorySize;



	
	
		
};
