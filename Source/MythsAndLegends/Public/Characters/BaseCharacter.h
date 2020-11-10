// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MythsAndLegends/Public/Characters/SkillComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter()
	{
		SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill Component"));
	}

	FORCEINLINE USkillComponent* GetSkillComponent() const { return SkillComponent; }


	FORCEINLINE class UBehaviorTree* GetBT() const { return BehaviorTree; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowProtectedAccess="true"))
	class UBehaviorTree* BehaviorTree;

	USkillComponent* SkillComponent;
};
