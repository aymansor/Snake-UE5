#include "SnakeGameModeBase.h"
#include "SnakeHead.h"
#include "Arena.h"
#include "Fruit.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Snake/SnakeHud.h"
#include "Snake/SnakeSaveGame.h"
#include "Snake/ASnakePlayerController.h"
#include "Components/AudioComponent.h"

ASnakeGameModeBase::ASnakeGameModeBase()
{
	DefaultPawnClass = ASnakeHead::StaticClass();
	HUDClass = ASnakeHud::StaticClass();
	PlayerControllerClass = ASnakeGameModeBase::StaticClass();

	bViewDebugLines = false;

	ArenaHeight = 1500;
	ArenaWidth = 1700;

	SquareWidth = 100.f;

	ArenaSpawnCenter = FVector(50, -50, 0);

	// Camera Location
	CameraHeight = ArenaHeight * 1.2;
	CameraSpawnLocation = FVector(50.0, -50.0, CameraHeight);
	CameraSpawnRotation = FRotator(-90.0, 0.0, 0.0);

}

void ASnakeGameModeBase::StartPlay()
{
	Super::StartPlay();

	LoadGame();
	SpawnCamera();
	SpawnArena();
	SpawnFruit();

	BackgroundAudioComponent = PlaySound(BackgroundSoundCue);
}

void ASnakeGameModeBase::SpawnCamera()
{
	ACameraActor* PlayerViewCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraSpawnLocation, CameraSpawnRotation, FActorSpawnParameters());
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC)
	{
		PlayerViewCamera->SetOwner(PC);
		PC->SetViewTarget(PlayerViewCamera);
	}
}

void ASnakeGameModeBase::GameOver()
{
	SaveGame();
	Arena->GetStaticMeshComponent()->SetMaterial(0, Arena->ArenaGameOverMaterial);

	AASnakePlayerController* SnakePlayerController = Cast<AASnakePlayerController>(GetWorld()->GetFirstPlayerController());

	if (SnakePlayerController) 
	{
		SnakePlayerController->ToggleGameOverMenu();
	}
}

FVector ASnakeGameModeBase::GetBottomPoint() const
{
	return FVector(-(ArenaHeight / 2), -(ArenaWidth / 2), 1) + ArenaSpawnCenter;
}

UAudioComponent* ASnakeGameModeBase::PlaySound(USoundBase* Sound)
{
	if (Sound)
	{
		return UGameplayStatics::SpawnSound2D(this, Sound);
	}

	return nullptr;
}

void ASnakeGameModeBase::StopPlayingMusic()
{
	if (BackgroundAudioComponent)
	{
		BackgroundAudioComponent->FadeOut(1.0f, 0.0f);
	}
}

void ASnakeGameModeBase::SpawnArena()
{
	FTransform SpawnTransform = FTransform(FRotator(), ArenaSpawnCenter, FVector(ArenaHeight, ArenaWidth, 1));
	Arena = GetWorld()->SpawnActor<AArena>(ArenaClass, SpawnTransform, FActorSpawnParameters());

	// For debugging the grid
	ViewDebugLines();
}

void ASnakeGameModeBase::SpawnFruit()
{
	const float GridHighet = 0.0f;

	FVector TopLeft = GetBottomPoint();

	// random point in the grid
	float SpawnX = FMath::RandRange(0, ArenaHeight /100 - 1);
	float SpawnY = FMath::RandRange(0, ArenaWidth /100 - 1);
	float SpawnYaw = FMath::FRandRange(0.f, 360.f);

	// upper left and lower right point of the box on for the random box in the grid
	FVector UpperLeft = TopLeft + FVector(SpawnX * SquareWidth, SpawnY * SquareWidth, GridHighet);
	FVector LowerRight = TopLeft + FVector(SpawnX * SquareWidth + SquareWidth, SpawnY * SquareWidth + SquareWidth, GridHighet);

	// mid point formula to get the mid point location for the box
	FVector SpawnLocation = FVector(((UpperLeft.X + LowerRight.X) / 2.0f), ((UpperLeft.Y + LowerRight.Y) / 2.0f), 5.0f);
	FRotator SpawnRotation = FRotator(0.0f, SpawnYaw, 0.0f);

	GetWorld()->SpawnActor<AFruit>(FruitClass, SpawnLocation, SpawnRotation, FActorSpawnParameters());

}

void ASnakeGameModeBase::CreateGrid()
{
	FVector TopLeft = GetBottomPoint();
	float GridHighet = 1.f;

	for (int32 i = 0; i < ArenaHeight /100 + 1; i++)
	{
		FVector Start = TopLeft + FVector(i * SquareWidth, 0.f, GridHighet);
		FVector End = Start + FVector(0.f, ArenaWidth, GridHighet);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}

	for (int32 i = 0; i < ArenaWidth /100 + 1; i++)
	{
		FVector Start = TopLeft + FVector(0.f, i * SquareWidth, GridHighet);
		FVector End = Start + FVector(ArenaHeight, 0.f, GridHighet);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}
}

void ASnakeGameModeBase::PlacePointOnGrid()
{
	float GridHighet = 1.f;

	FVector TopLeft = GetBottomPoint();

	for (int32 i = 0; i < ArenaHeight/100; i++)
	{
		for (int32 j = 0; j < ArenaWidth/100; j++)
		{
			FVector UpperLeft = TopLeft + FVector(i * SquareWidth, j * SquareWidth, GridHighet);
			FVector LowerRight = TopLeft + FVector(i * SquareWidth + SquareWidth, j * SquareWidth + SquareWidth, GridHighet);
			FVector RandomPointInSquare = FVector(((UpperLeft.X + LowerRight.X) / 2.0f), ((UpperLeft.Y + LowerRight.Y) / 2.0f), 5.0f);
			DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.f, FColor::Orange, true);
			DrawDebugCircle(GetWorld(), RandomPointInSquare, 25.f, 48, FColor::Purple, true, -1.f, 0, 2.5f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f), true);
		}
	}
}

void ASnakeGameModeBase::ViewDebugLines()
{
	if (bViewDebugLines)
	{
		CreateGrid();
		PlacePointOnGrid();
	}
}

void ASnakeGameModeBase::UpdateHUD()
{
	ASnakeHud* SnakeHud = Cast<ASnakeHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SnakeHud)
	{
		SnakeHud->UpdateCurrentScore(Score);

		if (Score > HighestScore)
		{
			HighestScore = Score;
			SnakeHud->UpdateHighestScore(HighestScore);
			SaveGame();
		}
	}
}

void ASnakeGameModeBase::SaveGame()
{
	if (USnakeSaveGame* SaveGameInstance = Cast<USnakeSaveGame>(UGameplayStatics::CreateSaveGameObject(USnakeSaveGame::StaticClass())))
	{
		SaveGameInstance->SnakeHighestScore = HighestScore;

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, FString("SaveSlot1"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Save succeeded."));
		}
	}
}

void ASnakeGameModeBase::LoadGame()
{
	// Retrieve and cast the USaveGame object to UMySaveGame.
	if (UGameplayStatics::DoesSaveGameExist(FString("SaveSlot1"), 0))
	{
		USnakeSaveGame* LoadedGame = Cast<USnakeSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("SaveSlot1"), 0));

		if (LoadedGame)
		{
			// The operation was successful, so LoadedGame now contains the data we saved earlier.
			UE_LOG(LogTemp, Warning, TEXT("Loading score save:"));
			HighestScore = LoadedGame->SnakeHighestScore;
			ASnakeHud* SnakeHud = Cast<ASnakeHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (SnakeHud)
			{
				SnakeHud->UpdateCurrentScore(Score);
				SnakeHud->UpdateHighestScore(HighestScore);
			}
			UE_LOG(LogTemp, Warning, TEXT("> Load succeeded | HighestScore: %d"), HighestScore);
		}
	}
}

void ASnakeGameModeBase::IncreaseScore()
{
	Score++;
}

void ASnakeGameModeBase::OnSnakeOverlapFruit()
{
	ASnakeHead* Snake = Cast<ASnakeHead>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Snake)
	{
		Snake->SpawnTail();
		IncreaseScore();
		UpdateHUD();
		SpawnFruit();
	}
}
