// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/ShowCaseLevel.h"
#include "Components/TextRenderComponent.h"

void AShowCaseLevel::ToggleUpperOne()
{
	Upper_1_Loaded = !Upper_1_Loaded;
	if(Upper_1_Loaded)
	{
		LoadNextLevel(FName("Upper_1"));
	} else
	{
		UnloadLevel(FName("Upper_1"));
	}
}
