// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/ML_PlayerController.h"
#include "MythsAndLegends/Public/Controllers/PlayerAiController.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Characters/NPC.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"


#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

AML_PlayerController::AML_PlayerController()
{
    // Enable the mouse cursor
    bShowMouseCursor = true;
    // TODO: Change the default cursor

    // Setup the tree
    BT_Component = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BT_Component"));
    BB_Component = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BB_Component"));

    TargetObject = nullptr;
    TargetIsEnemy = false;
    MinTargetDistance = 120.0f;
}


void AML_PlayerController::BeginPlay()
{
    SetupTree();
}

void AML_PlayerController::MeleeAttack()
{
    
    
    if(ABaseCharacter* const NPC = Cast<ABaseCharacter>(TargetObject))
    {
        if(ABaseCharacter* const PlayerCharacter  = Cast<ABaseCharacter>(GetPawn()))
        NPC->GetSkillComponent()->TakeDamage(PlayerCharacter->GetSkillComponent()->CalculateDamage());
    }
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
        if(auto* const HitActor = Cast<AActor>(HitResult.Actor))
        {
            if(HitActor->ActorHasTag("Landscape"))
            {
                MoveToPosition(HitResult.Location);
            } else
            {
                TargetObject = HitActor;
                if(HitActor->ActorHasTag("Enemy"))
                {
                    TargetIsEnemy = true;
                }
                MoveToTarget(HitResult.Location);
            }
        }
    }
}

void AML_PlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if(TargetObject)
    {
        if(!TargetIsEnemy)
        {
            if(IsTargetInRange())
            {
                PerformInteractWithTarget();
            }
        } else
        {
            if(IsTargetInRange())
            {
                PerformInteractWithTarget();
            }
        }
    }
}

void AML_PlayerController::MoveToPosition(FVector const MovePosition)
{
    TargetObject = nullptr;
    TargetIsEnemy = false;
    UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MovePosition);
}

void AML_PlayerController::MoveToTarget(FVector const Location)
{
    if(!TargetIsEnemy)
    {
        UE_LOG(LogTemp, Warning, TEXT("Moving To Target"));
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TargetObject->GetActorLocation());
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy"))
        if(ANPC* const NPC = Cast<ANPC>(TargetObject))
        {
            
            UAIBlueprintHelperLibrary::SimpleMoveToActor(this, NPC);
            UE_LOG(LogTemp, Warning, TEXT("Moving to enemy"));
        } else
        {
            TargetObject = nullptr;
            TargetIsEnemy = false;
        }
    }
}

bool AML_PlayerController::IsTargetInRange()
{
    if(!TargetObject)
        return false;

    float const DistanceBetween = FVector::Dist(TargetObject->GetActorLocation(), GetPawn()->GetActorLocation());
    
    if(DistanceBetween < MinTargetDistance)
    {
        return true;
    }
    
    return false;
    
}

void AML_PlayerController::PerformInteractWithTarget()
{
    if(!TargetIsEnemy)
    {
        // TODO: Loop through all the potenial tags and determine the next course of actions
    } else
    {
        // TODO: Check Attack Type
        MeleeAttack();
        
    }
    
    TargetObject = nullptr;
    TargetIsEnemy = false;
}

void AML_PlayerController::TraceOverItem()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    if(HitResult.bBlockingHit)
    {
        if(ABaseItem* const HitItem = Cast<ABaseItem>(HitResult.Actor))
        {
            UE_LOG(LogTemp, Warning, TEXT("OVER BASE ITEM"));
        }
    }
}





