// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/ItemUIClass.h"
#include "Components/TextBlock.h"

void UItemUIClass::SetupBasicDetails(ABaseItem* Owner, const FName& l_ItemName, const FText& l_ItemDescription)
{
	ItemOwner = Owner;
	// Convert the FName to FText & Set the text

	ItemName->SetText(FText::FromName(l_ItemName));
	ItemDescription->SetText(l_ItemDescription);
}
