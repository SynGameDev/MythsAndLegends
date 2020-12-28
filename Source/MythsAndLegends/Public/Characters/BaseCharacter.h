// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/BaseAIController.h"
#include "GameFramework/Character.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"
#include "BaseCharacter.generated.h"


UCLASS()
class MYTHSANDLEGENDS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void Attack();

	virtual void SpecialAttack(int32 const SpecialAttackIndex);
	virtual void SetAttackCooldown(float const time);

	virtual float GetMinAttackDistance() const;

	FORCEINLINE class USkillComponent* GetSkillComponent() const { return SkillComponent; }
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	FORCEINLINE class UBehaviorTree* GetBT() const { return BehaviorTree; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	FORCEINLINE virtual void PlayerDead() { IsDead = true; }
	FORCEINLINE bool IsCharacterDead() const { return IsDead; }

	FORCEINLINE bool IsSpecialAttackUnlocked(FSpecialAttack Attack) const
	{
		// TODO: Check if the player has the attack
		return true;
	}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowProtectedAccess="true"))
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills", meta=(AllowProtectedAccess="true"))
	USkillComponent* SkillComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Status", meta=(AllowPrivateAccess="true"))
	bool IsDead;

	TArray<FSpecialAttack> UnlockedSpecialAttacks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EDITOR|Draw Debug", meta=(AllowProtectedAccess="true"))
	bool DrawDebugShapes;

	// Attack Variables
	bool CanPerformSpecialAttack;
	FTimerHandle SpecialAttackCooldown;
	virtual void ResetSpecialAttack();
};
