// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/ML_PlayerController.h"

#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"

AML_PlayerController::AML_PlayerController()
{
    // Enable the mouse cursor
    bShowMouseCursor = true;
    // TODO: Change the default cursor
    
    
}

void AML_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("SetDestination", IE_Pressed, this, &AML_PlayerController::MoveToDestination);
}

void AML_PlayerController::MoveToDestination()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    if(HitResult.bBlockingHit)
    {
        // Hit Impact Point
        //GetPawn()->SetActorLocation(HitResult.ImpactPoint);
        
    }
}
