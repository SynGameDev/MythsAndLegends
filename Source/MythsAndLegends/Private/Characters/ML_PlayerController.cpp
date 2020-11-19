// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/ML_PlayerController.h"
#include "MythsAndLegends/Public/Controllers/PlayerAiController.h"
#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Characters/NPC.h"
#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/UI/MainHUD.h"


#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "UMG/Public/Blueprint/UserWidget.h"

AML_PlayerController::AML_PlayerController()
{
    // Enable the mouse cursor
    bShowMouseCursor = true;
    // TODO: Change the default cursor

    // Setup the tree
    BT_Component = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BT_Component"));
    BB_Component = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BB_Component"));

    // Initialize the variables
    TargetObject = nullptr;
    TargetIsEnemy = false;
    MinTargetDistance = 120.0f;

    ItemHovering = nullptr;
    CanAttack = true;
}


void AML_PlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetupTree();
    
}

void AML_PlayerController::MeleeAttack()
{
    if(!CanAttack)
        return;
    
    // Get the players current target and Insure that it's a NPC
    if(ABaseCharacter* const NPC = Cast<ABaseCharacter>(TargetObject) )
    {
        // Valid data that we are the player & deriving from the base character class
        // Than Apply the damage to the NPC
        if(ABaseCharacter* const PlayerCharacter  = Cast<ABaseCharacter>(GetPawn()))
        {
            PlayerCharacter->Attack();
            NPC->GetSkillComponent()->TakeDamage(PlayerCharacter->GetSkillComponent()->CalculateDamage());
            CanAttack = false;
        }
    }
}

void AML_PlayerController::SetAttackCooldown(float const Time)
{
    GetWorld()->GetTimerManager().SetTimer(AttackCooldownTh, this, &AML_PlayerController::ResetCanAttack, Time, false);
}

void AML_PlayerController::ResetCanAttack()
{
    CanAttack = true;
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
    InputComponent->BindAction("Inventory", IE_Pressed, this, &AML_PlayerController::ToggleInventoryUI);
}

void AML_PlayerController::MoveToDestination()
{
    // Create a trace that will return the trace to hit result
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    // If we are hitting something than move the character to this position
    if(HitResult.bBlockingHit)
    {
        // make sure that we are hitting an actor
        if(auto* const HitActor = Cast<AActor>(HitResult.Actor))
        {
            
            // TODO: Add an array of different movement settings
            // If the actor has a tag that is landscape and move towards the click position
            if(HitActor->ActorHasTag("Landscape"))
            {
                MoveToPosition(HitResult.Location);
            } else
            {
                // Otherwise the hit is a target object so we assign it, then check if it's an enemy
                // If it is an enemy we than set the boolean and start moving towards target.
                TargetObject = HitActor;
                if(HitActor->ActorHasTag("Enemy"))
                {
                    // Set the booleans 
                    TargetIsEnemy = true;
                    TargetIsPickable = false;
                    // Get the player character & than the UI to make sure it's valid,
                    // Then set the target of the enemy
                    if(auto* const PlayerChar = Cast<APlayerCharacter>(GetPawn()))
                    {
                        if(auto* UI = Cast<UMainHUD>(PlayerChar->GetMainUI()))
                        {
                            UI->SetEnemyTarget(Cast<ABaseCharacter>(HitActor)->GetSkillComponent());
                        }
                    }
                } else if(HitActor->ActorHasTag("Item"))
                {
                    TargetIsEnemy = false;
                    TargetIsPickable = true;
                }
                MoveToTarget(HitResult.Location);
            }
        }
    }
}

void AML_PlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Check our distance from the target object. if we are in range than perform action on that target object
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
                if(auto* PlayerChar = Cast<APlayerCharacter>(GetPawn()))
                {
                    if(auto* UI = Cast<UMainHUD>(PlayerChar->GetMainUI()))
                    {
                        UI->StartEnemyTargetTimer();
                    }
                }
            }
        }
    }
    
    TraceOverItem();
}

void AML_PlayerController::BeginPlayingState()
{
    Super::BeginPlayingState();
    SetupUI();
}

void AML_PlayerController::MoveToPosition(FVector const MovePosition)
{
    // Set the target to null so we aren't following any target objects & that we are looking for an enemy
    TargetObject = nullptr;
    TargetIsEnemy = false;
    TargetIsPickable = false;
    // Move to the location
    UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MovePosition);

    if(auto* PlayerChar = Cast<APlayerCharacter>(GetPawn()))
    {
        if(auto* UI = Cast<UMainHUD>(PlayerChar->GetMainUI()))
        {
            UI->UnsetEnemyTarget();
        }
    }
}

void AML_PlayerController::MoveToTarget(FVector const Location)
{
    // Check whether we are looking for a enemy or not
    if(!TargetIsEnemy)
    {
        // Start Moving towards the location of the target
        // (this target isn't moving so we use simpleMoveToLocation instead of actor)
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TargetObject->GetActorLocation());
    } else
    {

        // Check & Make sure that the Target is a NPC if it's valid than move to the actor,
        // Otherwise we unset the target object & enemy to false
        if(ANPC* const NPC = Cast<ANPC>(TargetObject))
        {
            UAIBlueprintHelperLibrary::SimpleMoveToActor(this, NPC);
        } else
        {
            TargetObject = nullptr;
            TargetIsEnemy = false;
        }
    }
}

bool AML_PlayerController::IsTargetInRange()
{
    // Ensure we have a target object
    if(!TargetObject)
        return false;

    // Get the distance between the player & the target object, if we are within range than return true otherwise false
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
        if(TargetIsPickable)
        {

            if(auto* PlayerChar = Cast<ABaseCharacter>(GetPawn()))
            {
                PlayerChar->GetInventoryComponent()->PickupItem(Cast<ABaseItem>(TargetObject));
                
                TargetObject = nullptr;
                TargetIsPickable = false;
            }
        }
    } else
    {
        MeleeAttack();
    }
    
    TargetObject = nullptr;
    TargetIsEnemy = false;
}

void AML_PlayerController::TraceOverItem()
{
    // Perform a raytrace under the mouse
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    // Make sure that we hit something
    if(HitResult.bBlockingHit)
    {
        // If it's a Base item than check if we we're already hovering over an item & that it's not the same item
        // Remove the Outline, than add new outline to the new item
        if(ABaseItem* const HitItem = Cast<ABaseItem>(HitResult.Actor))
        {
            if(ItemHovering && ItemHovering != HitItem)
                ItemHovering->HideOutline();

            ItemHovering = HitItem;
            ItemHovering->ShowOutline();
        } else
        {
            // If we aren't hitting an item than if a item is assign remove the outline
            if(ItemHovering)
                ItemHovering->HideOutline();
            
            ItemHovering = nullptr;
        }
    } else
    {
        // If we aren't hitting an item than if a item is assign remove the outline
        if(ItemHovering)
            ItemHovering->HideOutline();
        
        ItemHovering = nullptr;
    }
}

void AML_PlayerController::SetupUI()
{
    auto* PlayerChar = Cast<APlayerCharacter>(GetPawn());
    
    if(PlayerChar->sub_MainHUD)
    {
        PlayerChar->MainHUD = CreateWidget<UUserWidget>(this, PlayerChar->sub_MainHUD);
        PlayerChar->MainHUD->AddToViewport();
    }
}

void AML_PlayerController::ToggleInventoryUI()
{
    // Validate the Pawn as player Character 
    if(auto* PlayerChar = Cast<APlayerCharacter>(GetPawn()))
    {
        // Validate the HUD as a MainHUD and toggle the inventory
        if(UMainHUD* HUD = Cast<UMainHUD>(PlayerChar->GetMainUI()))
        {
            HUD->OpenInventory(this);
        }
    }
}





