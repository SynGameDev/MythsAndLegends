// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
    BT_Component = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BT_Component"));
    BB_Component = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BB_Component"));
    
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    // Cast the InPawn to a base character & make sure that it's valid before continuing.
    if(ABaseCharacter* const Character = Cast<ABaseCharacter>(InPawn))
    {
        // Make sure that the character has a black board & Initialize it
        if(Character->GetBT()->BlackboardAsset)
        {
            BB_Component->InitializeBlackboard(*(Character->GetBT()->BlackboardAsset));
        }
        // Start the BT
        BT_Component->StartTree(*Character->GetBT());
    }
}
