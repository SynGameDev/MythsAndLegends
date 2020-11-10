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

private:
    void SetupTree() const;
    virtual void SetupInputComponent() override;
    void MoveToDestination();
};
