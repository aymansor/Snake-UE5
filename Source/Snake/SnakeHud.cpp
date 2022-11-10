#include "SnakeHud.h"
#include "SnakeWidget.h"
#include "GameOver.h"
#include "Snake/PauseMenu.h"
#include "Snake/SettingsMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void ASnakeHud::DrawHUD()
{
	Super::DrawHUD();
}

void ASnakeHud::BeginPlay()
{
	Super::BeginPlay();

	CreateSnakeWidget();
	CreatePauseMenuWidget();
	CreateSettingsMenuWidget();
}

void ASnakeHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ASnakeHud::CreateSnakeWidget()
{
	if (SnakeWidgetClass)
	{
		SnakeWidget = CreateWidget<USnakeWidget>(GetWorld(), SnakeWidgetClass);

		if (SnakeWidget)
		{
			SnakeWidget->AddToViewport();
		}
	}
}

void ASnakeHud::CreatePauseMenuWidget()
{
	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuWidgetClass);

		if (PauseMenuWidget)
		{
			// Set the widget visibility to hidden than add to the view port
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
			PauseMenuWidget->AddToViewport();
		}
	}
}

void ASnakeHud::CreateSettingsMenuWidget()
{
	if (SettingsWidgetClass)
	{
		SettingsWidget = CreateWidget<USettingsMenu>(GetWorld(), SettingsWidgetClass);

		if (SettingsWidget)
		{
			// Set the widget visibility to hidden than add to the view port
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
			SettingsWidget->AddToViewport();
		}
	}
}

void ASnakeHud::UpdateCurrentScore(int Value)
{
	if (SnakeWidget)
	{
		SnakeWidget->UpdateCurrentScoreCount(Value);
	}
}

void ASnakeHud::UpdateHighestScore(int Value)
{
	if (SnakeWidget)
	{
		SnakeWidget->UpdateHighestScoreCount(Value);
	}
}

void ASnakeHud::ShowGameOverWidget()
{
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOver>(GetWorld(), GameOverWidgetClass);

		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GameOverWidget->bIsFocusable = true;
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), GameOverWidget);
		}
	}
}

void ASnakeHud::ShowPauseMenuWidget()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(this, true);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		PauseMenuWidget->bIsFocusable = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), PauseMenuWidget);
	}
}

void ASnakeHud::HidePauseMenuWidget()
{
	if (PauseMenuWidgetClass)
	{
		if (PauseMenuWidget)
		{
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
			UGameplayStatics::SetGamePaused(this, false);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
			PauseMenuWidget->bIsFocusable = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
		}
	}
}

void ASnakeHud::ShowSettingsMenuWidget()
{
	if (PauseMenuWidget->GetIsVisible())
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (SettingsWidget)
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
		SettingsWidget->bIsFocusable = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), SettingsWidget);
	}
}

void ASnakeHud::HideSettingsMenuWidget()
{
	if (SettingsWidgetClass)
	{
		if (SettingsWidget)
		{
			SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
			PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
