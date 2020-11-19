// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Items/BaseWeapon.h"

#include "Materials/MaterialInstanceConstant.h"

ABaseWeapon::ABaseWeapon()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTable (TEXT("DataTable'/Game/DataTables/WeaponDataTable.WeaponDataTable'"));
    if(DataTable.Succeeded())
    {
        WeaponDataTable = DataTable.Object;
    }

    SpawnInWorld = true;
}

void ABaseWeapon::SpawnWeapon()
{

    static const FString ContextString = "Weapon Table Context";
    FString SpawnWeaponID = "";
    TArray<FName> ItemNames = WeaponDataTable->GetRowNames();

    if(SpawnItemID == "")
    {
        SpawnItemID = ItemNames[FMath::RandRange(0, ItemNames.Num() - 1)];
    }

    FWeaponTable* const WeaponData = WeaponDataTable->FindRow<FWeaponTable>(SpawnItemID, ContextString, true);
    if(WeaponData)
    {
        static const FString ItemDataContext = "Item Table Context";
        FItemDataTable* ItemData = ItemDataTable->FindRow<FItemDataTable>(SpawnItemID, ItemDataContext, true);
        if(ItemData)
        {
            // --- BASE DETAILS --- //
            ItemName = ItemData->ItemName;
            ItemDescription = ItemData->ItemDescription;
            ItemTier = ItemData->ItemTier;
            ItemMesh->SetStaticMesh(ItemData->ItemMesh);
            MeshOutline->SetStaticMesh(ItemData->ItemMesh);
            MeshOutline->SetMaterial(0, ItemData->OutlineMaterial);
            // --- WEAPON DETAILS --- //
            MinDamage = WeaponData->MinDamage;
            MaxDamage = WeaponData->MaxDamage;
            WeaponType = WeaponData->WeaponType;
            SocketName = WeaponData->SocketAttachmentName;
            AttackMontages = WeaponData->AttackAnimations;
        }
    }
}

void ABaseWeapon::SpawnWeapon(FName WeaponName)
{
    SpawnItemID = WeaponName;
    SpawnWeapon();
}

void ABaseWeapon::SpawnWeapon(bool Spawn)
{
    SpawnInWorld = Spawn;
    SpawnWeapon();
}

void ABaseWeapon::SpawnWeapon(FName WeaponName, bool Spawn)
{
    SpawnInWorld = Spawn;
    SpawnItemID = WeaponName;
    SpawnWeapon();
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    if(SpawnInWorld)
    {
        SpawnWeapon();
    }
}
