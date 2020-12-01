// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Engine/DataTable.h"
#include "BaseConsumable.generated.h"

UENUM(BlueprintType)
enum EConsumableType
{
	Health,
	Mana,
	Defence,
	Attack,
	Stamina
};

USTRUCT(BlueprintType)
struct FConsumableDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* ConsumingAnimation;
	UPROPERTY(EditAnywhere)
	bool IsHealthConsumable;
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EConsumableType>> ConsumableTypes;
	
	UPROPERTY(EditAnywhere, Category="Health Boost", meta=(EditCondition="IsHealthConsumable"))
	float HealthIncrement;
	UPROPERTY(EditAnywhere, Category="Health Boost", meta=(EditCondition="IsHealthConsumable"))
	float DefenceIncrement;
	
};


UCLASS()
class MYTHSANDLEGENDS_API ABaseConsumable : public ABaseItem
{
	GENERATED_BODY()
public:
	ABaseConsumable();

	void SpawnWeapon();
	void SpawnWeapon(bool Spawn);
	void SpawnWeapon(FName WeaponName);
	void SpawnWeapon(FName WeaponName, bool Spawn);
	virtual void BeginPlay() override;

	

	void UseItem(class USkillComponent* const CharacterSkillComponent);
	void UseHealthPotion(class USkillComponent* const CharacterSkillComponent);

	FORCEINLINE class UAnimMontage* GetAnimMontage() const { return ConsumingAnimation; }

	

private:
	UPROPERTY(EditAnywhere, Category="General", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UAnimMontage* ConsumingAnimation;
	UPROPERTY(EditAnywhere, Category="General", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool IsHealthConsumable;
	UPROPERTY(EditAnywhere, Category="General", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<TEnumAsByte<EConsumableType>> ConsumableTypes;

	UPROPERTY(EditAnywhere, Category="Health Boost", BlueprintReadOnly, meta=(EditCondition="IsHealthConsumable", AllowPrivateAccess="true"))
	float HealthIncrement;
	UPROPERTY(EditAnywhere, Category="Health Boost", BlueprintReadOnly, meta=(EditCondition="IsHealthConsumable", AllowPrivateAccess="true"))
	float DefenceIncrement;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UDataTable* ConsumableDataTable;
};
