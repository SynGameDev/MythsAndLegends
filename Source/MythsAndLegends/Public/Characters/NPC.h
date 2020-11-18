// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/AI_Task/AITargetPoint.h"
#include "NPC.generated.h"

UENUM(Blueprintable)
enum EMovementState
{
    Wander,
    Follow,
    Path,
    Attack
};
UCLASS()
class MYTHSANDLEGENDS_API ANPC : public ABaseCharacter
{
	GENERATED_BODY()
public:
    ANPC();

    virtual void BeginPlay() override; 
    FORCEINLINE float GetMinAttackDistance() const { return AttackDistance; }

    FORCEINLINE AAITargetPoint* GetPatrolPoints() const { return PatrolPoint;}
    FORCEINLINE int32 GetCurrentTargetIndex() const { return CurrentTargetIndex; }
    FORCEINLINE void SetNextTarget(bool const increment) { if(increment) { CurrentTargetIndex++; } else { CurrentTargetIndex--; }}
    FORCEINLINE EMovementState GetMovementState() const { return MovementState; }
    void SetMovementState(EMovementState const NewState);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Testing|Attack System")
    bool WillAttackPlayer;

    
private:
    
    UFUNCTION()
    void OnSeePlayer(APawn* Pawn);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Sense", meta=(AllowPrivateAccess="true"))
    class UPawnSensingComponent* PawnSensingComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack Settings", meta=(AllowPrivateAccess="true"))
    float AttackDistance;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
    TEnumAsByte<EMovementState> MovementState;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Targets", meta=(AllowPrivateAccess="true"))
    AAITargetPoint* PatrolPoint;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Targets", meta=(AllowPrivateAccess="true"))
    int32 CurrentTargetIndex;

    
    

};
