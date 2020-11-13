// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/MainHUD.h"

#include "Characters/BaseCharacter.h"
#include "Components/SizeBox.h"
#include "UMG/Public/Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"

#include "Kismet/GameplayStatics.h"

UMainHUD::UMainHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    
}

void UMainHUD::OpenInventory(APlayerController* Controller)
{
    if(!InventoryWidgetClass && InventoryContainer)
        return;

    // Toggle The Inventory Variables
    IsInventoryOpen = !IsInventoryOpen;
    // If the inventory variable is true, than create a Widget of the inventory & add it to the HUD
    // Otherwise close the inventory & remove any inventory Widgets
    if(IsInventoryOpen)
    {
        InventoryWidget = WidgetTree->ConstructWidget<UWidget>(InventoryWidgetClass);
        InventoryContainer->AddChild(InventoryWidget);
    } else
    {
        SelectedItemPoint->ClearChildren();
        InventoryContainer->RemoveChild(InventoryWidget);
        InventoryWidget = nullptr;
    }
}

void UMainHUD::SetupTimers()
{
    
}

void UMainHUD::SetEnemyTarget(USkillComponent* NewTarget)
{
    // Set the new target
    TargetSkillComponent = NewTarget;
    // Display the Enemy Health bar
    EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void UMainHUD::StartEnemyTargetTimer()
{
    // Start a timer, once it runs out it will remove the target
    GetWorld()->GetTimerManager().SetTimer(ThEnemyTarget, this, &UMainHUD::UnsetEnemyTarget, 10.0f, false);
}

void UMainHUD::UnsetEnemyTarget()
{
    // Set the target to be null
    TargetSkillComponent = nullptr;
    // Hide the Progressbar
    EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUD::UpdatePlayerHealth()
{
    // Get the player character, get the skilll component & create the percentage
    if(auto* const PlayerChar = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        PlayerHealth = PlayerChar->GetSkillComponent()->GetCharacterHealth() / 100;
    }
}

void UMainHUD::UpdateEnemyHealth()
{
    if(!TargetSkillComponent)
        return;

    EnemyHealth = TargetSkillComponent->GetCharacterHealth() / 100;
}
