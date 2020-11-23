// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
    UCharacterAnimInstance();
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    float GetCurrentSpeed() const;
    class ABaseCharacter* GetOwningCharacter() const;
    bool CheckIfGrounded() const;
private:
    float Speed;
    bool IsGrounded;
    class ABaseCharacter* OwningCharacter;
    
};
