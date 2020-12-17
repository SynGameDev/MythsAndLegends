// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Levels/BaseLevelScript.h"
#include "ShowCaseLevel.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API AShowCaseLevel : public ABaseLevelScript
{
	GENERATED_BODY()
public:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loaded Levels", meta=(AllowPrivateAccess="true"))
	bool Upper_1_Loaded;

	UFUNCTION(BlueprintCallable)
	void ToggleUpperOne();

	
	
};
