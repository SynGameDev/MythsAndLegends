// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter()
	{
		SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill Component"));
		WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
		WeaponMesh->SetupAttachment(GetMesh());

		InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	}

	virtual void Attack()
	{
		if(InventoryComponent->GetEquippedWeapon())
		{
			if(auto* const Weapon = Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon()))
			{
				//PlayAnimMontage(Weapon->GetAttackAnimation());
			}
		}
	}

	FORCEINLINE USkillComponent* GetSkillComponent() const { return SkillComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	FORCEINLINE class UBehaviorTree* GetBT() const { return BehaviorTree; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowProtectedAccess="true"))
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills", meta=(AllowProtectedAccess="true"))
	USkillComponent* SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack Anim", meta=(AllowProtectedAccess="true"));
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Mesh", meta=(AllowProtectedAccess="true"))
	UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowProtectedAccess="true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowProtectedAccess="true"))
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowProtectedAccess="true"))
	float RunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowProtectedAccess="true"))
	float CrouchSpeed;
	
};
