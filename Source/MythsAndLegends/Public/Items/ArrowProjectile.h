#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowProjectile.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API AArrowProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AArrowProjectile();

    void FireArrow(const FVector& FireDirection);

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    class UCapsuleComponent* CapsuleComponent;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    class UStaticMeshComponent* ProjectileMesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    class UProjectileMovementComponent* ProjectileMovementComponent;
    
};
