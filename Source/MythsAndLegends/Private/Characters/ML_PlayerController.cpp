// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/ML_PlayerController.h"
#include "MythsAndLegends/Public/Controllers/PlayerAiController.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AML_PlayerController::AML_PlayerController()
{
    // Enable the mouse cursor
    bShowMouseCursor = true;
    // TODO: Change the default cursor

    // Setup the tree
    BT_Component = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BT_Component"));
    BB_Component = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BB_Component"));
}


void AML_PlayerController::BeginPlay()
{
    SetupTree();
}

void AML_PlayerController::SetupTree() const
{
    if(ABaseCharacter* const Char = Cast<ABaseCharacter>(GetOwner()))
    {
        // Make sure that the character has a black board & Initialize it
        if(Char->GetBT()->BlackboardAsset)
        {
            BB_Component->InitializeBlackboard(*(Char->GetBT()->BlackboardAsset));
        }
        // Start the BT
        BT_Component->StartTree(*Char->GetBT());
    }
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

    // If we are hitting something than move the character to this position
    if(HitResult.bBlockingHit)
    {
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitResult.Location);
    }
}
