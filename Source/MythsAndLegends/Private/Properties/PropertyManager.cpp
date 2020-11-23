// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Properties/PropertyManager.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APropertyManager::APropertyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	RootComponent = BoxComponent;
	
	ClosedPropertyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Closed Mesh"));
	ClosedPropertyMeshOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline Mesh"));
	OpenPropertyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Opened Mesh"));

	ClosedPropertyMesh->SetupAttachment(RootComponent);
	ClosedPropertyMeshOutline->SetupAttachment(ClosedPropertyMesh);
	OpenPropertyMesh->SetupAttachment(RootComponent);

	this->Tags.Add("Property");
	
	OpenPropertyMesh->SetVisibility(false, true);

	IsPropertyOpen = false;
}

void APropertyManager::ToggleProperty()
{
	IsPropertyOpen = !IsPropertyOpen;
	if(IsPropertyOpen)
	{
		OpenPropertyMesh->SetVisibility(true);
		ClosedPropertyMesh->SetVisibility(false);
	} else
	{
		OpenPropertyMesh->SetVisibility(false);
		ClosedPropertyMesh->SetVisibility(true);
	}
}

