// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

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
    
protected:
	class UBehaviorTreeComponent* BT_Component;
	class UBlackboardComponent* BB_Component;

	UPROPERTY(EditDefaultsOnly, Category="AI|Keys")
	FName MoveToLocation;

	virtual void OnPossess(APawn* InPawn) override;
	
};
