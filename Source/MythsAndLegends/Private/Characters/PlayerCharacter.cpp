// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/PlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    // Create & Setup objects
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERA BOOM"));
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FOLLOW CAMERA"));

    
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
