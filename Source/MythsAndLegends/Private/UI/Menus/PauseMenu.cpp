#include "MythsAndLegends/Public/UI/Menus/PauseMenu.h"


#include "Characters/ML_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	// On click event context 
	ContinueButton->OnClicked.AddDynamic(this, &UPauseMenu::ContinueGame);
	SaveGameButton->OnClicked.AddDynamic(this, &UPauseMenu::SaveGame);
	LoadGameButton->OnClicked.AddDynamic(this, &UPauseMenu::LoadGame);
	OptionsButton->OnClicked.AddDynamic(this, &UPauseMenu::OpenOptions);
	ExitGameButton->OnClicked.AddDynamic(this, &UPauseMenu::ExitGame);
	
}

void UPauseMenu::ContinueGame()
{
	UGameplayStatics::SetGamePaused(this, false);
	if(auto* const PlayerController = Cast<AML_PlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->TogglePauseMenu();
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to unpause game"));
	}
}

void UPauseMenu::SaveGame()
{
	
}

void UPauseMenu::LoadGame()
{
	
}

void UPauseMenu::OpenOptions()
{
	
}

void UPauseMenu::ExitGame()
{
	
}
