// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/AttackEnemy.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "MythsAndLegends/Public/Characters/NPC.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/PlayerCharacter.h"
#include "UI/MainHUD.h"

UAttackEnemy::UAttackEnemy()
{
    NodeName = "Attack Enemy";
}

EBTNodeResult::Type UAttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    // Validate the AI Controller
    if(auto* NPC_Controller = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        // Get the character from the Controller
        ABaseCharacter* const NPC = Cast<ABaseCharacter>(NPC_Controller->GetPawn());

        if(!NPC->IsCharacterDead())
        {
            // Get the target from the blackboard & make sure that it's a BaseCharcter prior to proceeding
            if(auto* PawnTarget = Cast<ABaseCharacter>(
                NPC_Controller->GetBlackboardComponent()->GetValueAsObject(NPC_Controller->Target)))
            {
                // Get the distance from between the NPC & the target character
                float Distance = FVector::Dist(NPC_Controller->GetPawn()->GetActorLocation(), PawnTarget->GetActorLocation());
                // If the the distance is within the target range, make the NPC attack and apply damage to the Target
                if(Distance < Cast<ANPC>(NPC_Controller->GetPawn())->GetMinAttackDistance())
                {
                    NPC->Attack();
                    PawnTarget->GetSkillComponent()->TakeDamage(NPC->GetSkillComponent()->CalculateDamage());
                    // If the pawn target is the player than cast the UI to get the UI and enemy the enemy health bar
                    if(auto* const PlayerChar = Cast<APlayerCharacter>(PawnTarget))
                    {
                        if(auto* const UI = Cast<UMainHUD>(PlayerChar->GetMainUI()))
                        {
                            UI->SetEnemyTarget(NPC->GetSkillComponent());
                        }
                    }
                }   
            
            }
        }
    }
    // Return the task completed
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
