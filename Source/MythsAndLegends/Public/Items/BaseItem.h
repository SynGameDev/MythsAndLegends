// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum EItemTier
{
	COMMON,
    UNCOMMON,
    RARE,
    LEGENDARY
};

UENUM(BlueprintType)
enum EItemType
{
	Consumable,
	Weapon,
	Crafting,
	Misc
};

USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	// --- ITEM DETAILS --- //
	UPROPERTY(EditAnywhere)
	FString ItemID;
	UPROPERTY(EditAnywhere)
	FName ItemName;
	
	// Name of the item that will be displayed in the UI
	UPROPERTY(EditAnywhere)
	FString ItemUIName;
	UPROPERTY(EditAnywhere)
	FText ItemDescription;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemTier> ItemTier;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemType> ItemType;
	UPROPERTY(EditAnywhere)
	UTexture* ItemIcon;



	// --- ITEM MESH --- //
	UPROPERTY(EditAnywhere)
	class UStaticMesh* ItemMesh;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* OutlineMaterial;
};


UCLASS()
class MYTHSANDLEGENDS_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	// Displaying Outline
	bool IsBeingHovered;
	void ShowOutline();

	void HideOutline();

	
	


	
	FORCEINLINE UStaticMeshComponent* GetItemMesh() const { return ItemMesh; }
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE FText GetItemDesc() const { return ItemDescription; }
protected:


	virtual void BeginPlay() override;
    void SetupCommonDetails();
    	
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details", meta=(AllowProtectedAccess="true"))
	UImage* ItemImage;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn Details", meta=(AllowProtectedAccess="true"))
	FName SpawnItemID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn Details", meta=(AllowProtectedAccess="true"))
	bool SpawnInWorld;
	class UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Containers", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> CommonItemWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Containers", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> UncommonItemWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Containers", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> RareItemWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Containers", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> GodItemWidget;

	// UI Data
	FString ItemUIName;
	
	UWidgetComponent* ItemWidget;

	
	
};
