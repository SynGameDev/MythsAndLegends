// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "PlayerAiController.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API APlayerAiController : public ABaseAIController
{
	GENERATED_BODY()
public:
    APlayerAiController();

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Blackboard Keys", meta=(AllowPrivateAccess="true"))
    FName MoveToPosition;
};
