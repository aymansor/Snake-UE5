#include "SettingsMenu.h"
#include "Components/Button.h"
#include "ASnakePlayerController.h"

void USettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ExitSettingsButton->OnClicked.AddUniqueDynamic(this, &USettingsMenu::ExitSettingsMenu);
	HighResolutionButton->OnClicked.AddUniqueDynamic(this, &USettingsMenu::EnableHighResolution);
	MediumResolutionButton->OnClicked.AddUniqueDynamic(this, &USettingsMenu::EnableMediumResolution);
	LowResolutionButton->OnClicked.AddUniqueDynamic(this, &USettingsMenu::EnableLowResolution);
}

void USettingsMenu::ExitSettingsMenu()
{
	AASnakePlayerController* SnakePlayerController = Cast<AASnakePlayerController>(GetWorld()->GetFirstPlayerController());

	if (SnakePlayerController)
	{
		SnakePlayerController->ToggleSettingsMenu();
	}
}

void USettingsMenu::EnableHighResolution()
{
	GetOwningPlayer()->ConsoleCommand("r.ScreenPercentage 100");
	GetOwningPlayer()->ConsoleCommand("sg.PostProcessQuality 3");
	GetOwningPlayer()->ConsoleCommand("sg.ShadowQuality 3");
}

void USettingsMenu::EnableMediumResolution()
{
	GetOwningPlayer()->ConsoleCommand("r.ScreenPercentage 80");
	GetOwningPlayer()->ConsoleCommand("sg.PostProcessQuality 2");
	GetOwningPlayer()->ConsoleCommand("sg.ShadowQuality 2");
}

void USettingsMenu::EnableLowResolution()
{
	GetOwningPlayer()->ConsoleCommand("r.ScreenPercentage 50");
	GetOwningPlayer()->ConsoleCommand("sg.PostProcessQuality 1");
	GetOwningPlayer()->ConsoleCommand("sg.ShadowQuality 1");
}

FReply USettingsMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		ExitSettingsMenu();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
