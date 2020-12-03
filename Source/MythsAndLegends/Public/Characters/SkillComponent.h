// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTHSANDLEGENDS_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

	void TakeDamage(float Damage);
	float CalculateDamage();
	
	// --- GETTERS --- //
	FORCEINLINE float GetCharacterHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetAttackStamina() const { return AttackStamina; }

	
	FORCEINLINE float GetAccuracy() const { return Accuracy; }
	FORCEINLINE float GetStrength() const { return Strength; }
	FORCEINLINE float GetCharisma() const { return Charisma; }
	FORCEINLINE float GetIntelligence() const { return Intelligence; }

	FORCEINLINE bool AddHealth(float const HealthAmount);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Base Details", meta=(AllowPrivateAccess="true"))
	FName CharacterName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Health", meta=(AllowPrivateAccess="true"))
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Health", meta=(AllowPrivateAccess="true"))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Stamina", meta=(AllowPrivateAccess="true"))
	float AttackStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Stamina", meta=(AllowPrivateAccess="true"))
	float AttackStaminaDecrementRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Stamina", meta=(AllowPrivateAccess="true"))
	float AttackStaminaRegenerateRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Basic Details|Stamina", meta=(AllowPrivateAccess="true"))
	FTimerHandle RegenTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Standard", meta=(AllowPrivateAccess="true"))
	float Accuracy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Standard", meta=(AllowPrivateAccess="true"))
	float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Standard", meta=(AllowPrivateAccess="true"))
	float Charisma;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Skills|Standard", meta=(AllowPrivateAccess="true"))
	float Intelligence;
	




		
};

