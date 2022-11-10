#include "PauseMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Snake/SnakeGameModeBase.h"
#include "Components/CheckBox.h"
#include "ASnakePlayerController.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode = Cast<ASnakeGameModeBase>(GetWorld()->GetAuthGameMode());
	check(GameMode);

	RestartGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::RestartSnakeGame);
	QuitGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::QuitSnakeGame);
	ResumeGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::ResumeGame);
	SettingsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::ShowSettingsMenu);
	GodModeButton->OnCheckStateChanged.AddDynamic(this, &UPauseMenu::GodMode);
}

void UPauseMenu::RestartSnakeGame()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->RestartLevel();
}

void UPauseMenu::QuitSnakeGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UPauseMenu::ResumeGame()
{
	AASnakePlayerController* SnakePlayerController = Cast<AASnakePlayerController>(GetWorld()->GetFirstPlayerController());

	if (SnakePlayerController)
	{
		SnakePlayerController->TogglePauseMenu();
	}
}

void UPauseMenu::GodMode(bool bIsChecked)
{
	if (GameMode)
	{
		GameMode->bIsGodModeEnabled = bIsChecked;
	}
}

void UPauseMenu::ShowSettingsMenu()
{
	AASnakePlayerController* SnakePlayerController = Cast<AASnakePlayerController>(GetWorld()->GetFirstPlayerController());

	if (SnakePlayerController)
	{
		SnakePlayerController->ToggleSettingsMenu();
	}
}

FReply UPauseMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		RestartSnakeGame();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::Q)
	{
		QuitSnakeGame();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		ResumeGame();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}