// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/MoveToPositionNode.h"
#include "MythsAndLegends/Public/Controllers/PlayerAiController.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMoveToPositionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Get the player controller
   if( APlayerAiController* PlayerController = Cast<APlayerAiController>(OwnerComp.GetAIOwner()))
   {
       UBlackboardComponent* BB_Comp = PlayerController->GetBlackboardComponent();
       
   }
    
}
