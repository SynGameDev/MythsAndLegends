// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectedInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class MYTHSANDLEGENDS_API USelectedInventoryItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Details")
	FText ItemDesc;

	UFUNCTION(BlueprintCallable)
	void SetValues(FName const Name, FText const Desc);
	
	
};
