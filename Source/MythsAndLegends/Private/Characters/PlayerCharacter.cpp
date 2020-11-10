// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


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

    
}

void APlayerCharacter::Test()
{
    
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
