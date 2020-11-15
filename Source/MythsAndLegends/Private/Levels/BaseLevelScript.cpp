// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Levels/BaseLevelScript.h"
#include "Kismet/GameplayStatics.h"

ABaseLevelScript::ABaseLevelScript()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABaseLevelScript::LoadNextLevel(FName LevelName)
{
    FLatentActionInfo Info;
    UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, Info);
}

void ABaseLevelScript::UnloadLevel(FName LevelName)
{
    FLatentActionInfo Info;
    UGameplayStatics::UnloadStreamLevel(this, LevelName, Info, true);
}
