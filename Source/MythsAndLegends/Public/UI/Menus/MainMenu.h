#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta=(BindWidgetOptional))
	class UImage* BackgroundImage;
	UPROPERTY(meta=(BindWidget))
	class UButton* NewGameButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* LoadGameButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* OptionsButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* ExitButton;

	UFUNCTION()
	void StartNewGame();
	UFUNCTION()
	void OpenSavedGames();
	UFUNCTION()
	void LoadGame();
	UFUNCTION()
	void OpenOptions();
	UFUNCTION()
	void CloseGame();
};
