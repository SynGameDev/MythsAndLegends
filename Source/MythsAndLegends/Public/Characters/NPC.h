// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "NPC.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API ANPC : public ABaseCharacter
{
	GENERATED_BODY()
public:
    ANPC();


    virtual void BeginPlay() override;
    
private:
    UFUNCTION()
    void OnSeePlayer(APawn* Pawn);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Sense", meta=(AllowPrivateAccess="true"))
    class UPawnSensingComponent* PawnSensingComponent;

};
