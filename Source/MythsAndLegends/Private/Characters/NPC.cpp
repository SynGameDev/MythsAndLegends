// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/NPC.h"
#include "Perception/PawnSensingComponent.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;

    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sense Component"));
    PawnSensingComponent->SetPeripheralVisionAngle(50.0f);

    WillAttackPlayer = true;
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
    if(PawnSensingComponent)
    {
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &ANPC::OnSeePlayer);
    }

    SetMovementState(MovementState);
    if(auto* const NPC_Controller = Cast<ABaseAIController>(GetController()))
    {
        NPC_Controller->GetBlackboardComponent()->SetValueAsBool(NPC_Controller->TEST_PT_WillAttack, WillAttackPlayer);
    }
}

void ANPC::SetMovementState(EMovementState const NewState)
{
    MovementState = NewState;
    if(auto* const Con = Cast<ABaseAIController>(GetController()))
    {
        Con->GetBlackboardComponent()->SetValueAsEnum(Con->MovementState, NewState);
    }
}

void ANPC::PlayerDead()
{
    Super::PlayerDead();
    if(auto* const Contr = Cast<ABaseAIController>(GetController()))
    {
        Contr->GetBlackboardComponent()->SetValueAsBool(Contr->IsCharacterDead, true);
    }
}

void ANPC::OnSeePlayer(APawn* Pawn)
{
    UE_LOG(LogTemp, Warning, TEXT("SEEN PAWN"));
    if(auto* const AI_Con = Cast<ABaseAIController>(GetController()))
    {
        // TODO: Filter through the seen target to see if it's an enemy
        if(auto* PlayerChar = Cast<APlayerCharacter>(Pawn))
        {
            AI_Con->SetOnSeenTarget(Pawn);
            SetMovementState(EMovementState::Attack);
        }
    }
}
