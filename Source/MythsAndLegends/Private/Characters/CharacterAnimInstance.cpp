// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Characters/CharacterAnimInstance.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MythsAndLegends/Public/Characters/InventoryComponent.h"
#include "MythsAndLegends/Public/Items/BaseWeapon.h"


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

    if(OwningCharacter->IsCharacterDead())
        return;

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
    return Cast<ABaseCharacter>(GetOwningActor());
}

bool UCharacterAnimInstance::CheckIfGrounded() const
{
    if(!OwningCharacter)
        return true;

    return OwningCharacter->GetCharacterMovement()->IsFalling();

    
}

void UCharacterAnimInstance::ShootArrow()
{
    if(!OwningCharacter)
        return;

    if(auto* const Weapon = Cast<ABaseWeapon>(OwningCharacter->GetInventoryComponent()->GetEquippedWeapon()))
    {
        if(Weapon->GetWeaponType() == EWeaponType::RANGED)
        {
            Weapon->ShootArrow(OwningCharacter->GetActorForwardVector());
        }
    }
}
