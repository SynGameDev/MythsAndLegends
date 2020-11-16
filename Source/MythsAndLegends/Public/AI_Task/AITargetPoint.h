// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AITargetPoint.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API AAITargetPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAITargetPoint();

	TArray<FVector> GetTargetPoints() const { return TargetPoints; }
	FVector GetTargetPointPosition(int32 TargetPointIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Targets", meta=(AllowPrivateAccess="true", MakeEditWidget="true"))
	TArray<FVector> TargetPoints;
	
};
