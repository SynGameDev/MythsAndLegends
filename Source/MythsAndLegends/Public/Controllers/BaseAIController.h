// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UENUM()
enum EEnemyStatus
{
	WANDER,
	FOLLOW,
	ATTACK,
	QUEST
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys")
	FName Target = "Target";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackbaord Keys")
	FName Key_EnemyStatus = "EnemyStatus";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blackboard Keys")
	FName Key_TargetDistance;

	// --- TARGETS --- //
	class ABaseCharacter* TargetObject;

	void SetOnSeenTarget(APawn* Pawn);
	TEnumAsByte<EEnemyStatus> EnemyStatus;
    
protected:
	class UBehaviorTreeComponent* BT_Component;
	class UBlackboardComponent* BB_Component;
	
	virtual void OnPossess(APawn* InPawn) override;

	
	
};
