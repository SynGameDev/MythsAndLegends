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
    
    if(auto* NPC_Controller = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        ABaseCharacter* const NPC = Cast<ABaseCharacter>(NPC_Controller->GetPawn());
       
        if(auto* PawnTarget = Cast<ABaseCharacter>(
            NPC_Controller->GetBlackboardComponent()->GetValueAsObject(NPC_Controller->Target)))
        {
            float Distance = FVector::Dist(NPC_Controller->GetPawn()->GetActorLocation(), PawnTarget->GetActorLocation());
            if(Distance < Cast<ANPC>(NPC_Controller->GetPawn())->GetMinAttackDistance())
            {
                Cast<ABaseCharacter>(NPC_Controller->GetPawn())->Attack();
                PawnTarget->GetSkillComponent()->TakeDamage(NPC->GetSkillComponent()->CalculateDamage());

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
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
