// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/CharacterAnimInstance.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
    Speed = 0.0f;
    IsGrounded = false;
    OwningCharacter = nullptr;
}

void UCharacterAnimInstance::NativeBeginPlay()
{
    OwningCharacter = GetOwningCharacter();
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    if(!OwningCharacter)
        OwningCharacter = GetOwningCharacter();

    Speed = GetCurrentSpeed();
    IsGrounded = CheckIfGrounded();
    
}

float UCharacterAnimInstance::GetCurrentSpeed() const
{
    if(!OwningCharacter)
        return 0.0f;

    return OwningCharacter->GetVelocity().Size();
}

ABaseCharacter* UCharacterAnimInstance::GetOwningCharacter() const
{
    return Cast<ABaseCharacter>(GetOwningCharacter());
}

bool UCharacterAnimInstance::CheckIfGrounded() const
{
    if(!OwningCharacter)
        return true;

    return OwningCharacter->GetCharacterMovement()->IsFalling();

    
}
