#include "MythsAndLegends/Public/Characters/SkillComponent.h"

USkillComponent::USkillComponent()
{
    MaxHealth = 100;
    CurrentHealth = 100;
}

void USkillComponent::TakeDamage(float Damage)
{
    // TODO: Calcutate any damage resistant points due to armour
    CurrentHealth -= Damage;

    if(CurrentHealth <= 0)
    {
        GetOwner()->Destroy();
    }
}

float USkillComponent::CalculateDamage()
{
    // ** THIS WILL BE REPLACED ONCE THEIR IS AN EQUIPPED WEAPON
    float const MinDmg = 7;
    float const MaxDmg = 13;

    // Generate the damage that will be applied
    float const DamageToApply = FMath::RandRange(MinDmg, MaxDmg);

    // Calculate whether we may miss or not
    float MissPoints = 100;
    MissPoints -= ((Accuracy / 100) - (AttackStamina / 100));
    UE_LOG(LogTemp, Warning, TEXT("MissPoints ACS: %f"), MissPoints);
    // TODO: Apply Booster

    // Determine the Miss
    float const Missed = FMath::RandRange(0.0f, 100.0f);

    // If the Missed value is larger than missed points, return 0.0 as we have missed
    if(Missed > MissPoints)
        return 0.0f;

    // Return the damage to apply
    return DamageToApply;
    
    
}
