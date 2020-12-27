#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta=(BindWidgetOptional))
	class UImage* BackgroundImage;
	UPROPERTY(meta=(BindWidget))
	class UButton* ContinueButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* SaveGameButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* LoadGameButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* OptionsButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* ExitGameButton;

	UFUNCTION(BlueprintCallable)
	void ContinueGame();
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	UFUNCTION(BlueprintCallable)
	void OpenOptions();
	UFUNCTION(BlueprintCallable)
	void ExitGame();
	
};
