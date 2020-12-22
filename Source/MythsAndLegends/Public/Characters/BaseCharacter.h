// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "ML_PlayerController.h"
#include "Controllers/BaseAIController.h"
#include "GameFramework/Character.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
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

		IsDead = false;
	}

	virtual void Attack()
	{
		UE_LOG(LogTemp, Warning, TEXT("Attacking"));
		if(InventoryComponent->GetEquippedWeapon())
		{
			if(auto* const Weapon = Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon()))
			{
				FAttackAnimation const AttackAnim = Weapon->GetAttackAnimation();
				UE_LOG(LogTemp, Warning, TEXT("Time: %f"), AttackAnim.AnimationTime);
				PlayAnimMontage(AttackAnim.AttackAnimation);
				if(auto* const NPC_Controller = Cast<ABaseAIController>(GetController()))
				{
					NPC_Controller->GetBlackboardComponent()->SetValueAsFloat(NPC_Controller->AttackCooldown, AttackAnim.AnimationTime);
                    
                } else if(auto* const PlayerController = Cast<AML_PlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
				{
					PlayerController->SetAttackCooldown(AttackAnim.AnimationTime);	
				}
			}
		} else
		{
			if(auto* const NPC_Controller = Cast<ABaseAIController>(GetController()))
			{
				NPC_Controller->GetBlackboardComponent()->SetValueAsFloat(NPC_Controller->AttackCooldown, 2.5f);
			} else if(auto* const PlayerController = Cast<AML_PlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
			{
				PlayerController->SetAttackCooldown(2.0f);
			}
		}
	}

	virtual float GetMinAttackDistance() const
	{
		if(InventoryComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon())->GetMinAttackDistance());
			return Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon())->GetMinAttackDistance();
		}

		return 120.0f;
	}

	FORCEINLINE USkillComponent* GetSkillComponent() const { return SkillComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	FORCEINLINE class UBehaviorTree* GetBT() const { return BehaviorTree; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	FORCEINLINE virtual void PlayerDead() { IsDead = true; }
	FORCEINLINE bool IsCharacterDead() const { return IsDead; }
	
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
	
};
