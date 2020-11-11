// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Controllers/PlayerAiController.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
    APlayerCharacter();

    FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
private:
    // --- COMPONENTS --- //
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    class UCameraComponent* CameraComponent;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    class USpringArmComponent* CameraBoom;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    class UInventoryComponent* InventoryComponent;

    virtual void Tick(float DeltaSeconds) override;
    

    
};