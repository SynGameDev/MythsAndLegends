// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/Public/Blueprint/UserWidget.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    // Create & Setup objects
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERA BOOM"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FOLLOW CAMERA"));
    CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    // Don't Rotate the player
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // Character Movement Component Rotation
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;
    
    // Camera & Camera Boom Rotation
    CameraComponent->bUsePawnControlRotation = false;
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritRoll = false;
    CameraBoom->bInheritYaw = false;

    CameraBoom->bDoCollisionTest = false;
    
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerCharacter::TraceToHideWall()
{
    FHitResult HitResult;
    FCollisionObjectQueryParams COQP;
    FCollisionQueryParams CQP;
    CQP.AddIgnoredActor(this);
    GetWorld()->LineTraceSingleByObjectType(HitResult, CameraComponent->GetRelativeLocation(), GetMesh()->GetRelativeLocation(), COQP, CQP);

    if(HitResult.bBlockingHit)
    {
        if(HitResult.GetActor()->ActorHasTag("HideWall"))
        {
            HitResult.GetActor()->SetHidden(true);
        }
    }
}


