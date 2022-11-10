#include "GameOver.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Input/Reply.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	RestartGameButton->OnClicked.AddUniqueDynamic(this, &UGameOver::RestartSnakeGame);
	QuitGameButton->OnClicked.AddUniqueDynamic(this, &UGameOver::QuitSnakeGame);
}

void UGameOver::RestartSnakeGame()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->RestartLevel();
}

void UGameOver::QuitSnakeGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

FReply UGameOver::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		RestartSnakeGame();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		QuitSnakeGame();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
