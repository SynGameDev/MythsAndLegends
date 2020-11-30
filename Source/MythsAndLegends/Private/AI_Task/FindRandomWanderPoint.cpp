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
    // Get the NPC Character & Controller, Make sure that they are valid
    if(auto* const NPC_Controller = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        if(auto* const NPC_Character = Cast<ANPC>(NPC_Controller->GetPawn()))
        {
            if(LimitedSearch && !NPC_Character->IsCharacterDead())
            {
                // Get the Origin point of the NPC & create  a nav location
                FVector const NPC_OriginPoint = NPC_Character->GetActorLocation();
                FNavLocation Location;

                // Get the current Navigation System and set a random point within the radius, set this point on the blackboard
                UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
                if(NavSystem->GetRandomPointInNavigableRadius(NPC_OriginPoint, SearchRadius, Location, nullptr))
                {
                    if(auto* const BB = NPC_Controller->GetBlackboardComponent())
                    {
                        BB->SetValueAsVector(NPC_Controller->TargetLocation, Location.Location);
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("NO BLACKBOARD"))
                    }
                } else
                {
                    // TODO: Wander Around point instead of the characters origin
                }
            }
        }
    }
    // Return the task completed
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
