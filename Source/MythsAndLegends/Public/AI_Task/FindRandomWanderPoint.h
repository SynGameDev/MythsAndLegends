// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "FindRandomWanderPoint.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UFindRandomWanderPoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
    UFindRandomWanderPoint();
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wander Data")
    bool LimitedSearch = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wander Data", meta=(EditCodition="LimitedSearch"))
    float SearchRadius;
};
