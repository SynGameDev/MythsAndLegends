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
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowPrivateAccess="true"))
	float MinDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowPrivateAccess="true"))
	float MaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowPrivateAccess="true"))
	TArray<class UAnimMontage*> AttackMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WeaponDetails", meta=(AllowPrivateAccess="true"))
	TEnumAsByte<EWeaponType> SwordType;
	
};
