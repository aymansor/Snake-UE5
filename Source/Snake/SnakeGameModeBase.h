#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASnakeGameModeBase();

private:
	class AArena* Arena;

	int32 ArenaWidth;

	int32 ArenaHeight;

	float SquareWidth;

	float CameraHeight;

	FVector ArenaSpawnCenter;

	FVector CameraSpawnLocation;

	FRotator CameraSpawnRotation;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Arena")
	TSubclassOf<class AArena> ArenaClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fruit")
	TSubclassOf<class AFruit> FruitClass;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Debug Lines")
	bool bViewDebugLines;

private:
	int Score;

	int HighestScore;

protected:
	void StartPlay() override;

private:
	class UAudioComponent* BackgroundAudioComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* BackgroundSoundCue = nullptr;

private:
	// Spawn the camera used by the player
	void SpawnCamera();

	// Spawn the play area
	void SpawnArena();

	// Draw a grid for debugging purposes
	void CreateGrid();

	// Draw points on the grid for debugging
	void PlacePointOnGrid();

	// Enable Debugging lines and points 
	void ViewDebugLines();

	// Save the highest score for the game (Called when game over and when achieving new highest score)
	void SaveGame();

	// Load the highest saved score (called on StartPlay)
	void LoadGame();

	// Update the HUD to reflect new score
	void UpdateHUD();

	// Updates the score count
	void IncreaseScore();

public:
	bool bIsGodModeEnabled = false;

public:
	void OnSnakeOverlapFruit();

	void SpawnFruit();

	void GameOver();

	FVector GetBottomPoint() const;

public:
	UAudioComponent* PlaySound(class USoundBase* Sound);

	void StopPlayingMusic();
};
