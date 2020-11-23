// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropertyManager.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API APropertyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropertyManager();

	void ToggleProperty();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* ClosedPropertyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* ClosedPropertyMeshOutline;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* OpenPropertyMesh;

	bool IsPropertyOpen;

	
	
	

};
