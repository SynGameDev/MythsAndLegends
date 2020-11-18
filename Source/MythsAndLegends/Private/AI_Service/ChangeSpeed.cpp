#include "MythsAndLegends//Public/AI_Service/ChangeSpeed.h"
#include "MythsAndLegends/Public/Characters/BaseCharacter.h"
#include "MythsAndLegends/Public/Controllers/BaseAIController.h"
#include "MythsAndLegends/Public/Characters/NPC.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

UChangeSpeed::UChangeSpeed()
{
    bNotifyBecomeRelevant = true;
    NodeName = TEXT("Change Speed");
}

FString UChangeSpeed::GetStaticServiceDescription() const
{
    return FString("Change the movement speed of the AI");
}

void UChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);
    // Get the controller & Character, make sure that they are valid
    if (auto* const NPC_Controller = Cast<ABaseAIController>(OwnerComp.GetOwner()))
    {
        if (auto* const NPC_Character = Cast<ANPC>(NPC_Controller->GetPawn()))
        {
            // Change the movement speed that will set on the BT
            NPC_Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
        }
    }
}
