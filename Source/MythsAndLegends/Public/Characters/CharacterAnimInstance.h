// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

UENUM(BlueprintType)
enum EEquippedWeaponInstance
{
    OneHandSword,
    TwoHandSword,
    BowAndArrow,
    Unarmed,
    Dead
};

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

    

    FORCEINLINE void SetWeaponInstance(EEquippedWeaponInstance const NewInst) { WeaponInstance = NewInst; }
    FORCEINLINE EEquippedWeaponInstance GetWeaponInstance() const { return WeaponInstance; }
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
    float Speed;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
    bool IsGrounded;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character", meta=(AllowPrivateAccess="true"))
    class ABaseCharacter* OwningCharacter;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Status", meta=(AllowPrivateAccess="true"))
    TEnumAsByte<EEquippedWeaponInstance> WeaponInstance;
    

    // --- BOW CALL BACKS --- //
    UFUNCTION(BlueprintCallable)
    void ShootArrow();
    
};
