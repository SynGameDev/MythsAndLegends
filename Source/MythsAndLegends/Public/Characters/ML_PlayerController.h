// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ML_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API AML_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AML_PlayerController();

    class UBehaviorTreeComponent* BT_Component;
    class UBlackboardComponent* BB_Component;

    virtual void BeginPlay() override;

    FORCEINLINE class UBlackboardComponent* GetBlackboard() const { return BB_Component; }

    void MeleeAttack();

private:
    void SetupTree() const;
    virtual void SetupInputComponent() override;
    void MoveToDestination();
    virtual void Tick(float DeltaSeconds) override;

    // Target Details
    class AActor* TargetObject;
    bool TargetIsEnemy;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Target Settings", meta=(AllowPrivateAccess="true"))
    float MinTargetDistance;
    

    // Movement Methods
    void MoveToPosition(FVector const MovePosition);
    void MoveToTarget(FVector const Location);
    bool IsTargetInRange();
    void PerformInteractWithTarget();

    // --- TRACES --- //
    void TraceOverItem();

    
};
