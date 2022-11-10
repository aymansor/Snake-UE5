#include "DeadZone.h"
#include "Snake/SnakeGameModeBase.h"
#include "SnakeHead.h"

void ADeadZone::OverlapedWithSnakeHead(ASnakeHead* SnakeHead)
{
	ASnakeGameModeBase* GameMode = Cast<ASnakeGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode && !GameMode->bIsGodModeEnabled)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside Deadzone"))
		SnakeHead->SetIsAlive(false);
		GameMode->StopPlayingMusic();
		GameMode->GameOver();
	}
}
