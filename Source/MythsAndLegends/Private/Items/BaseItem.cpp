// Fill out your copyright notice in the Description page of Project Settings.


#include "MythsAndLegends/Public/Items/BaseItem.h"
#include "MythsAndLegends/Public/UI/ItemUIClass.h"
// Sets default values

ABaseItem::ABaseItem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable (TEXT("DataTable'/Game/DataTables/ItemDataTable.ItemDataTable'"));
	if(DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}
		
	// Create the objects
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	MeshOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline Mesh"));
	ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Item Widget"));

	// Set the collider to be root component
	RootComponent = Collider;
	ItemMesh->SetupAttachment(RootComponent);
	MeshOutline->SetupAttachment(ItemMesh);
	ItemWidget->SetupAttachment(RootComponent);

	MeshOutline->SetVisibility(false);
	IsBeingHovered = false;
		
	// Add tags to this item
	Tags.Add(FName("Item"));
	Tags.Add(FName("Outline"));
	Tags.Add(FName("Pickable"));

	// Create the Widget Object
	ItemWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ItemWidget->SetDrawAtDesiredSize(true);
	ItemWidget->SetRelativeLocation(FVector(100.0f, 100.0f, 100.0f));

}

void ABaseItem::ShowOutline()
{
	MeshOutline->SetVisibility(true);
}

void ABaseItem::HideOutline()
{
	MeshOutline->SetVisibility(false);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	switch(ItemTier)
	{
		case EItemTier::COMMON:
			ItemWidget->SetWidgetClass(CommonItemWidget);
			break;
		case EItemTier::UNCOMMON:
			ItemWidget->SetWidgetClass(UncommonItemWidget);
			break;
		case EItemTier::RARE:
			ItemWidget->SetWidgetClass(RareItemWidget);
			break;
		case EItemTier::LEGENDARY:
			ItemWidget->SetWidgetClass(GodItemWidget);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("INVALID ITEM"));
			break;
	}

	SetupCommonDetails();
	
}

void ABaseItem::SetupCommonDetails()
{
	if(!ItemWidget->GetWidgetClass())
		return;

	if(auto* const Widget = Cast<UItemUIClass>(ItemWidget->GetUserWidgetObject()))
	{
		Widget->SetupBasicDetails(this, ItemUIName, ItemDescription);
	}
	
}
