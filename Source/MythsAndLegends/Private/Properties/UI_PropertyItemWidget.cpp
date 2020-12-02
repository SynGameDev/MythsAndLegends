#include "MythsAndLegends/Public/Properties/UI_PropertyItemWidget.h"
#include "Components/TextBlock.h"

void UUI_PropertyItemWidget::SetupItem(FText const Text)
{
	ItemText->SetText(Text);
}
