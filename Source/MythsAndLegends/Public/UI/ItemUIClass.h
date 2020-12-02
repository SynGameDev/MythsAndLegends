// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemUIClass.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MYTHSANDLEGENDS_API UItemUIClass : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetupBasicDetails(class ABaseItem* Owner, FText l_ItemName, FText l_ItemDescription);
	
protected:
	class ABaseItem* ItemOwner;
	
	UPROPERTY(meta=(BindWidget))
	class UImage* ItemBackground;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemDescription;
	
};
