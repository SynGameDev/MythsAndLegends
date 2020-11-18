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
    if(auto* const NPC_Con = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        int32 CurrentIndex = NPC_Con->GetBlackboardComponent()->GetValueAsInt(NPC_Con->TargetIndex);

        if(auto* const NPC_Char = Cast<ANPC>(NPC_Con->GetPawn()))
        {
            if((NPC_Char->GetPatrolPoints()->GetTargetPoints().Num() - 1) == CurrentIndex)
            {
                CurrentIndex = 0;
            } else
            {
                CurrentIndex++;
            }

            NPC_Con->GetBlackboardComponent()->SetValueAsInt(NPC_Con->TargetIndex, CurrentIndex);
            UE_LOG(LogTemp, Warning, TEXT("Incremented Path: %i"), CurrentIndex);
        }
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
