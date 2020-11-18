// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/AI_Task/AITargetPoint.h"

// Sets default values
AAITargetPoint::AAITargetPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AAITargetPoint::GetTargetPointPosition(int32 TargetPointIndex)
{
	// TODO: Implement Bidirectional trigger
	// check whether the target index is at the last index, if it is than set it to zero
	if(TargetPointIndex > TargetPoints.Num())
		return FVector::ZeroVector;

	// Get the next target target point
	return TargetPoints[TargetPointIndex];
}


