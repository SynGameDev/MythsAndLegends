// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Properties/PropertyManager.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
// Sets default values
APropertyManager::APropertyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Setup the box component
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	RootComponent = BoxComponent;

	// Create the property objects
	ClosedPropertyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Closed Mesh"));
	ClosedPropertyMeshOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline Mesh"));
	OpenPropertyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Opened Mesh"));
	// Create the property Widget
	PropertyActionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Property Action Menu"));
	// Create the position mesh
	EnterPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entry Position"));

	// Attach the objects
	ClosedPropertyMesh->SetupAttachment(RootComponent);
	ClosedPropertyMeshOutline->SetupAttachment(ClosedPropertyMesh);
	OpenPropertyMesh->SetupAttachment(RootComponent);
	PropertyActionWidget->SetupAttachment(RootComponent);
	EnterPosition->SetupAttachment(RootComponent);

	PropertyActionWidget->SetWidgetSpace(EWidgetSpace::Screen);

	this->Tags.Add("Property");
	
	OpenPropertyMesh->SetVisibility(false, true);

	IsPropertyOpen = false;
}

FVector APropertyManager::GetEntryPosition()
{
	const FVector LocalPos = EnterPosition->GetComponentLocation();
	return LocalPos;
}

void APropertyManager::ToggleProperty()
{
	if(!IsPropertyOpen)
	{
		IsPropertyOpen = true;
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ClosedPropertyMesh->SetVisibility(false);
		ClosedPropertyMeshOutline->SetVisibility(false);
		OpenPropertyMesh->SetVisibility(true);
	} else
	{
		IsPropertyOpen = false;
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ClosedPropertyMesh->SetVisibility(true);
		ClosedPropertyMeshOutline->SetVisibility(true);
		OpenPropertyMesh->SetVisibility(false);
	}
}
