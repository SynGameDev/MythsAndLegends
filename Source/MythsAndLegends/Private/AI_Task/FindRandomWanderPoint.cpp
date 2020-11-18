// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/FindRandomWanderPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "MythsAndLegends/Public/Characters/NPC.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "NavigationSystem/Public/NavigationSystem.h"

#include "GameFramework/CharacterMovementComponent.h"

UFindRandomWanderPoint::UFindRandomWanderPoint()
{
    NodeName = "Find Random Wander Point";
    LimitedSearch = true;
    SearchRadius = 1500.0f;
}

EBTNodeResult::Type UFindRandomWanderPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if(auto* const NPC_Controller = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        if(auto* const NPC_Character = Cast<ANPC>(NPC_Controller->GetPawn()))
        {
            if(LimitedSearch)
            {
                FVector const NPC_OriginPoint = NPC_Character->GetActorLocation();
                FNavLocation Location;

                UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
                if(NavSystem->GetRandomPointInNavigableRadius(NPC_OriginPoint, SearchRadius, Location, nullptr))
                {
                    if(auto* const BB = NPC_Controller->GetBlackboardComponent())
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Blackboard"))
                        BB->SetValueAsVector(NPC_Controller->TargetLocation, Location.Location);
                        
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("NO BLACKBOARD"))
                    }
                }
            }
        }
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
