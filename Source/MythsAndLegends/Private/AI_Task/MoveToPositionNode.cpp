// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/MoveToPositionNode.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ML_PlayerController.h"
#include "Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Characters/NPC.h"
#include "MythsAndLegends/Public/AI_Task/AITargetPoint.h"

UMoveToPositionNode::UMoveToPositionNode()
{
   NodeName = "Targeted Location";
}

EBTNodeResult::Type UMoveToPositionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

   if(auto* const NPC_Con = Cast<ABaseAIController>(OwnerComp.GetOwner()))
   {

      if(auto* const NPC_Char = Cast<ANPC>(NPC_Con->GetPawn()))
      {
         if(auto* const PatrolPath = NPC_Char->GetPatrolPoints())
         {

            // Get the current target index
            int32 const TargetIndex = NPC_Con->GetBlackboardComponent()->GetValueAsInt(NPC_Con->TargetIndex);
            // Get the location of that target point & Convert it to world space
            
            FVector const TargetLocation = PatrolPath->GetTargetPointPosition(TargetIndex);
            FVector const WorldTargetLocation = PatrolPath->GetActorLocation() + TargetLocation;

         
            //UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *TargetLocation.ToString());

            NPC_Con->GetBlackboardComponent()->SetValueAsVector(NPC_Con->TargetIndex, WorldTargetLocation);  
         }
      }
   }
   FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
   return EBTNodeResult::Succeeded;
}
