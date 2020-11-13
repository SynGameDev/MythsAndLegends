// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/NPC.h"
#include "Perception/PawnSensingComponent.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;

    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sense Component"));
    PawnSensingComponent->SetPeripheralVisionAngle(90.0f);
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
    if(PawnSensingComponent)
    {
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &ANPC::OnSeePlayer);
    }
}

void ANPC::OnSeePlayer(APawn* Pawn)
{
    UE_LOG(LogTemp, Warning, TEXT("SEEN PAWN"));
    if(auto* const AI_Con = Cast<ABaseAIController>(GetController()))
    {
        if(auto* PlayerChar = Cast<APlayerCharacter>(Pawn))
        {
            AI_Con->SetOnSeenTarget(Pawn);
        }
    }
}
