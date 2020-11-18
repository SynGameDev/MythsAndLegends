// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

USTRUCT(BlueprintType)
struct FBlackboardKeys
{
	GENERATED_BODY()
public:
	
};

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseAIController();
	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return BB_Component; }

	virtual void Tick(float DeltaSeconds) override;

	// --- BLACKBOARD KEYS --- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|General")
	FName MovementState = "MovementState";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|Targets")
	FName Target = "Target";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackbaord Keys|Targets")
	FName EnemyStatus = "EnemyStatus";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|Targets")
	FName TargetDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|Path")
	FName TargetIndex = "TargetIndex";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|Path")
	FName TargetLocation = "TargetLocation";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|Combat")
	FName AttackCooldown = "AttackCooldown";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys|Testing")
	FName TEST_PT_WillAttack = "PT_WillAttack";
	
	// --- TARGETS --- //
	class ABaseCharacter* TargetObject;

	void SetOnSeenTarget(APawn* Pawn);
    
protected:
	class UBehaviorTreeComponent* BT_Component;
	class UBlackboardComponent* BB_Component;
	
	virtual void OnPossess(APawn* InPawn) override;

	

	
	
};
