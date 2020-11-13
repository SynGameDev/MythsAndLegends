// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
public:

    UMainHUD(const FObjectInitializer& ObjectInitializer);

    // This will open the inventory
    UFUNCTION(BlueprintCallable)
    void OpenInventory(class APlayerController* Controller);

    // Set's up any timers
    UFUNCTION(BlueprintCallable)
    void SetupTimers();

    // --- Enemy Methods --- //
    void SetEnemyTarget(class USkillComponent* NewTarget);
    void StartEnemyTargetTimer();
    void UnsetEnemyTarget();

    // --- GETTERS --- //
    FORCEINLINE class USizeBox* GetSelectedItemPoint() const { return SelectedItemPoint; }
    FORCEINLINE UWidget* GetInventoryWidget() const { return InventoryWidget; }

private:
    // --- UI OBJECTS --- //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Widgets", meta=(AllowPrivateAccess="true"))
    class USizeBox* InventoryContainer;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|Variables", meta=(AllowPrivateAccess="true"))
    bool IsInventoryOpen = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Variables", meta=(AllowPrivateAccess="true"))
    TSubclassOf<UUserWidget> InventoryWidgetClass;
    class UWidget* InventoryWidget;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|Variables", meta=(AllowPrivateAccess="true"))
    class USizeBox* SelectedItemPoint;

    // --- PLAYERS --- //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|ProgressBasrs", meta=(AllowPrivateAccess="true"))
    float PlayerHealth;
    UFUNCTION(BlueprintCallable)
    void UpdatePlayerHealth();

    // --- ENEMY --- //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemies", meta=(AllowPrivateAccess="true"))
    class UProgressBar* EnemyHealthBar;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemies", meta=(AllowPrivateAccess="true"))
    class USkillComponent* TargetSkillComponent;
    UFUNCTION(BlueprintCallable)
    void UpdateEnemyHealth();

    // --- TIMERS --- //
    FTimerHandle ThEnemyTarget;
        
    
};