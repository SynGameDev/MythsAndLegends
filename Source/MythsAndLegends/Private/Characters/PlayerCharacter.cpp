// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
    
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}