// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseWeapon.generated.h"

UENUM()
enum EWeaponType
{
	ONE_HAND,
	TWO_HAND,
	RANGED,
	STAFF
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
	FORCEINLINE float GetMinDamage() const { return MinDamage; }
	FORCEINLINE float GetMaxDamage() const { return MaxDamage; }
	FORCEINLINE UAnimMontage* GetAttackAnimation() const { return AttackMontages[FMath::RandRange(0, AttackMontages.Num())]; }
	FORCEINLINE FName GetSocketName() const { return SocketName; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	float MinDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	float MaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	TArray<class UAnimMontage*> AttackMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowProtectedAccess="true"))
	TEnumAsByte<EWeaponType> SwordType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attachment|Socket", meta=(AllowPrivateAccess="true"))
	FName SocketName;
	
};
