// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Engine/DataTable.h"
#include "BaseWeapon.generated.h"

UENUM()
enum EWeaponType
{
	ONE_HAND,
	TWO_HAND,
	RANGED,
	STAFF
};

USTRUCT(BlueprintType)
struct FAttackAnimation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackAnimation;
	UPROPERTY(EditAnywhere)
	float AnimationTime;
};

USTRUCT(BlueprintType)
struct FWeaponTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float MinDamage;
	UPROPERTY(EditAnywhere)
	float MaxDamage;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EWeaponType> WeaponType;
	UPROPERTY(EditAnywhere)
	TArray<FAttackAnimation> AttackAnimations;
	UPROPERTY(EditAnywhere)
	FName SocketAttachmentName;
	UPROPERTY(EditAnywhere)
	float MinAttackDistance;
	
};

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()
public:
	ABaseWeapon();

	void SpawnWeapon();
	void SpawnWeapon(FName WeaponName);
	void SpawnWeapon(bool Spawn);
	void SpawnWeapon(FName WeaponName, bool Spawn);
	virtual void BeginPlay() override;

	void ShootArrow(const FVector FireDirection);
	
	UPROPERTY(EditAnywhere)
	class UDataTable* WeaponDataTable;
	
	FORCEINLINE float GetMinDamage() const { return MinDamage; }
	FORCEINLINE float GetMaxDamage() const { return MaxDamage; }
	FORCEINLINE FAttackAnimation GetAttackAnimation() const { return AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]; }
	FORCEINLINE FName GetSocketName() const { return SocketName; }
	FORCEINLINE float GetAttackCooldown() const { return AttackCooldownTime; }
	FORCEINLINE float GetMinAttackDistance() const { return MinAttackDistance; }
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	float MinDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	float MaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	TArray<FAttackAnimation> AttackMontages;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	float AttackCooldownTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	float MinAttackDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	TEnumAsByte<EWeaponType> WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attachment|Socket", meta=(AllowProtectedAccess="true"))
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bow And Arrow", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AArrowProjectile> ArrowProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bow And Arrow", meta=(AllowPrivateAccess="true"))
	FVector FirePoint;
	

	
};
