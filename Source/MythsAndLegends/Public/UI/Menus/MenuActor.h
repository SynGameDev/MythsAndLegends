#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MenuActor.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API AMenuActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMenuActor()
	{
		SceneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		RootComponent = SceneCamera;
	}

	UCameraComponent* SceneCamera;
	
};
