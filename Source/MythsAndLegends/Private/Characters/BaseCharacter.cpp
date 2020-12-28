#include "MythsAndLegends/Public/Characters/BaseCharacter.h"

#include "DrawDebugHelpers.h"
#include "Characters/ML_PlayerController.h"
#include "Controllers/BaseAIController.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"



ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill Component"));
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetMesh());

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	IsDead = false;
}

void ABaseCharacter::Attack()
{
	if(InventoryComponent->GetEquippedWeapon())
	{
		if(auto* const Weapon = Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon()))
		{
			FAttackAnimation const AttackAnim = Weapon->GetAttackAnimation();
			PlayAnimMontage(AttackAnim.AttackAnimation);
			SetAttackCooldown(AttackAnim.AnimationTime);
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

void ABaseCharacter::SpecialAttack(int32 const SpecialAttackIndex)
{
	if(auto* const PlayerController = Cast<AML_PlayerController>(GetController()))
		{
			if(PlayerController->CanPlayerAttack())
			{
				// Make sure that there is an equipped weapon & that it is valid
				if(InventoryComponent->GetEquippedWeapon())
				{
					if(auto* const Weapon = Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon()))
					{
						// Make sure the requested special attack is valid
						if(Weapon->GetTotalSpecialAttacks() >= SpecialAttackIndex)
						{
							// Get the Special attack and check that it's unlocked, if it is than run the attack
							FSpecialAttack const SpecialAttack = Weapon->GetSpecialAttack(SpecialAttackIndex);
							if(IsSpecialAttackUnlocked(SpecialAttack))
							{
								// Setup the attack Animation, play it & set the attack cooldown
								FAttackAnimation const AttackAnim = SpecialAttack.AttackAnim;
								PlayAnimMontage(AttackAnim.AttackAnimation);
								SetAttackCooldown(AttackAnim.AnimationTime);

								// Setup the sweep variable
								TArray<FHitResult> OutHits;
								FVector const ActorLocation = GetActorLocation();
								FCollisionShape const CollisionShape = FCollisionShape::MakeSphere(200.0f);

								// Draw Debug Shape
								if(DrawDebugShapes)
									DrawDebugSphere(GetWorld(), ActorLocation, CollisionShape.GetSphereRadius(), 100, FColor::Purple, true, 1.0f);
								
								// Check if there are any hits, if there is than loop through all the objects make sure that they
								// Are a Base Character & Deal damage to them
								bool const Hit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, ECC_WorldStatic, CollisionShape);
								if(Hit)
								{
									for(auto& hit : OutHits)
									{
										if(auto* const BaseCharacter = Cast<ABaseCharacter>(hit.GetActor()))
										{
											if(BaseCharacter != this)
											{
												BaseCharacter->GetSkillComponent()->TakeDamage(this->GetSkillComponent()->CalculateDamage() * SpecialAttack.DamageMultiplier);
											}
										}
									}
								}

								// TODO: Apply Special Attack Cooldown
							
							}
							
						} else
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("No Special Attack"));
						}
					}
				} else 
				{
					if(GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString("NO WEAPON EQUIPPED"));
					}
				}
			}
		} else
		{
			// TODO: AI Special Attack
		}
}

void ABaseCharacter::SetAttackCooldown(float const time)
{
	if(auto* const NPC_Controller = Cast<ABaseAIController>(GetController()))
	{
		NPC_Controller->GetBlackboardComponent()->SetValueAsFloat(NPC_Controller->AttackCooldown, time);
	} else if(auto* const PlayerController = Cast<AML_PlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->SetAttackCooldown(time);
	}
}

float ABaseCharacter::GetMinAttackDistance() const
{
	if(InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon())->GetMinAttackDistance());
		return Cast<ABaseWeapon>(InventoryComponent->GetEquippedWeapon())->GetMinAttackDistance();
	}

	return 120.0f;
}

