// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UAttackEnemy : public UBTTaskNode
{
	GENERATED_BODY()
public:
    UAttackEnemy();
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
