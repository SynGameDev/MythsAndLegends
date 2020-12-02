#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_PropertyItemWidget.generated.h"

UCLASS()
class MYTHSANDLEGENDS_API UUI_PropertyItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetupItem(FText const Text);

protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* ItemButton;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemText;
};
