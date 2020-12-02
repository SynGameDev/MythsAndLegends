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

	FVector GetEntryPosition();
	void ToggleProperty();

	FORCEINLINE FName GetPropertyName() const { return PropertyName; }
	FORCEINLINE bool IsPropertyAccessible() const { return IsAccessible; }
	FORCEINLINE class ABaseCharacter* GetPropertyOwner() const { return PropertyOwner; }
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* ClosedPropertyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* ClosedPropertyMeshOutline;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* OpenPropertyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UWidgetComponent* PropertyActionWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* EnterPosition;

	bool IsPropertyOpen;

	// Property Details
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Property Details", meta=(AllowPrivateAccess="true"))
	FName PropertyName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Property Details", meta=(AllowPrivateAccess="true"))
	bool IsAccessible;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Property Details", meta=(AllowPrivateAccess="true"))
	class ABaseCharacter* PropertyOwner;
	

};
