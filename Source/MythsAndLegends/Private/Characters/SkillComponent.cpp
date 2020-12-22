#include "MythsAndLegends/Public/Characters/SkillComponent.h"

#include "Characters/BaseCharacter.h"
#include "Characters/CharacterAnimInstance.h"

USkillComponent::USkillComponent()
{
    MaxHealth = 100;
    CurrentHealth = 100;
}

void USkillComponent::TakeDamage(float Damage)
{
    // Check if this is a player character, if it is than reduce the damage applied
    if(auto* const IsPlayer = Cast<APlayerCharacter>(GetOwner()))
    {
        Damage /= FMath::RandRange(1, 25);
    }
    // TODO: Calcutate any damage resistant points due to armour
    CurrentHealth -= Damage;

    // if the current Health is below 0, than get the base character, get the anim ref and set the anim instance
    if(CurrentHealth <= 0)
    {
        if(auto* const OwningCharacter = Cast<ABaseCharacter>(GetOwner()))
        {
            if(auto* const AnimRef = Cast<UCharacterAnimInstance>(OwningCharacter->GetMesh()->GetAnimInstance()))
            {
                AnimRef->SetWeaponInstance(EEquippedWeaponInstance::Dead);
                OwningCharacter->PlayerDead();
            }

            
        }
    }
}

float USkillComponent::CalculateDamage()
{

    if(auto* const Character = Cast<ABaseCharacter>(GetOwner()))
    {
        // Set the default values
        float MinDmg = 7;
        float MaxDmg = 13;

        // Get the weapon and make sure it's valid, if it is than update the values based on the weapons
        if(auto* const Weapon = Cast<ABaseWeapon>(Character->GetInventoryComponent()->GetEquippedWeapon()))
        {
            MinDmg = Weapon->GetMinDamage();
            MaxDmg = Weapon->GetMaxDamage();
        }

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

    return 3.0f;
    
}

bool USkillComponent::AddHealth(float const HealthAmount)
{
    // Check if we are already at max health, if we are than don't use the potion
    if(CurrentHealth == MaxHealth - 5)
        return false;

    // Otherwise, add the health amount, if it goes over the max than reset it
    CurrentHealth += HealthAmount;
    if(CurrentHealth > MaxHealth)
        CurrentHealth = MaxHealth;
    
    return true;
}
