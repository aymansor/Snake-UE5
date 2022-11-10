#include "ASnakePlayerController.h"
#include "Snake/SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeHud.h"

void AASnakePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &AASnakePlayerController::TogglePauseMenu);
	InputComponent->BindAction("ClearScore", IE_Pressed, this, &AASnakePlayerController::ClearScore);
}

void AASnakePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SnakeHud = Cast<ASnakeHud>(GetHUD());
	check(SnakeHud);
}

void AASnakePlayerController::TogglePauseMenu()
{
	if (SnakeHud)
	{
		bPauseMenuVisible ? SnakeHud->HidePauseMenuWidget() : SnakeHud->ShowPauseMenuWidget();
		bPauseMenuVisible = !bPauseMenuVisible;
	}
}

void AASnakePlayerController::ToggleSettingsMenu()
{
	if (SnakeHud)
	{
		bSettingsMenuVisible ? SnakeHud->HideSettingsMenuWidget() : SnakeHud->ShowSettingsMenuWidget();
		bSettingsMenuVisible = !bSettingsMenuVisible;
	}
}

void AASnakePlayerController::ToggleGameOverMenu()
{
	if (SnakeHud)
	{
		SnakeHud->ShowGameOverWidget();
	}
}

void AASnakePlayerController::ClearScore()
{
	if (UGameplayStatics::DeleteGameInSlot(FString("SaveSlot1"), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cleared score successfully!"))
	}
}