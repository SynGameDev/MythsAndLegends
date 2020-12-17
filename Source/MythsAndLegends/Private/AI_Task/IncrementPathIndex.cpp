// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/IncrementPathIndex.h"

#include <string>


#include "MythsAndLegends/Public/Characters/NPC.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UIncrementPathIndex::UIncrementPathIndex()
{
    NodeName = "Increment Path Index";
}

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UE_LOG(LogTemp, Warning, TEXT("Increment Path Index"));
    // Get the NPC Controller & Make sure that it's valid
    if(auto* const NPC_Con = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        // Get the current index from the black that will get us the path
        int32 CurrentIndex = NPC_Con->GetBlackboardComponent()->GetValueAsInt(NPC_Con->TargetIndex);

        // Get the NPC Character and make sure that it's valid
        if(auto* const NPC_Char = Cast<ANPC>(NPC_Con->GetPawn()))
        {

            // If we are at the max index, then set it to zero otherwise increment it
            if((NPC_Char->GetPatrolPoints()->GetTargetPoints().Num() - 1) == CurrentIndex)
            {
                CurrentIndex = 0;
            } else
            {
                CurrentIndex++;
            }
            // Set the blackboard
            NPC_Con->GetBlackboardComponent()->SetValueAsInt(NPC_Con->TargetIndex, CurrentIndex);
        }
        
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
