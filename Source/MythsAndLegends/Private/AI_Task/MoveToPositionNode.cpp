// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/MoveToPositionNode.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ML_PlayerController.h"
#include "Characters/PlayerCharacter.h"

UMoveToPositionNode::UMoveToPositionNode()
{
}

EBTNodeResult::Type UMoveToPositionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
   return EBTNodeResult::Succeeded;
}
