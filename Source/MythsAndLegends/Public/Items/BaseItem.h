// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "BaseItem.generated.h"

UENUM()
enum EItemTier
{
	COMMON,
	UNCOMMON,
	RARE,
	LEGENDARY
};

UCLASS()
class MYTHSANDLEGENDS_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem()
	{
		// Create the objects
		Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
		ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
		MeshOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline Mesh"));

		// Set the collider to be root component
		RootComponent = Collider;
		ItemMesh->SetupAttachment(RootComponent);
		MeshOutline->SetupAttachment(ItemMesh);

		MeshOutline->SetVisibility(false);
		IsBeingHovered = false;
		
		// Add tags to this item
		Tags.Add(FName("Item"));
		Tags.Add(FName("Outline"));
		Tags.Add(FName("Pickable"));

		
	}

	// Displaying Outline
	bool IsBeingHovered;
	void ShowOutline()
	{
		MeshOutline->SetVisibility(true);
	}

	void HideOutline()
	{
		MeshOutline->SetVisibility(false);
	}
	
	
	FORCEINLINE UStaticMeshComponent* GetItemMesh() const { return ItemMesh; }
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE FText GetItemDesc() const { return ItemDescription; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UBoxComponent* Collider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshOutline;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details", meta=(AllowProtectedAccess="true"))
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details", meta=(AllowProtectedAccess="true"))
	FText ItemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details", meta=(AllowProtectedAccess="true"))
	TEnumAsByte<EItemTier> ItemTier;

	
	
};
