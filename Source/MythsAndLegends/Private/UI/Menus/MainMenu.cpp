#include "MythsAndLegends/Public/UI/Menus/MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	NewGameButton->OnClicked.AddDynamic(this, &UMainMenu::StartNewGame);
	LoadGameButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSavedGames);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OpenOptions);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::UMainMenu::CloseGame);
}

void UMainMenu::StartNewGame()
{
	
}

void UMainMenu::OpenSavedGames()
{
	
}


void UMainMenu::LoadGame()
{
	
}

void UMainMenu::OpenOptions()
{
	
}

void UMainMenu::CloseGame()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}
