// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API ABaseLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
public:
    ABaseLevelScript();
protected:
    UFUNCTION(BlueprintCallable)
    virtual void LoadNextLevel(FName LevelName);
    UFUNCTION(BlueprintCallable)
    virtual void UnloadLevel(FName LevelName);
};
