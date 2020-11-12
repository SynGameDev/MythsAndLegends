// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/UI/SelectedInventoryItem.h"

void USelectedInventoryItem::SetValues(FName const Name, FText const Desc)
{
    ItemName = Name;
    ItemDesc = Desc;
}
