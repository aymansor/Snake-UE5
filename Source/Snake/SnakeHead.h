#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeHead.generated.h"

UCLASS()
class SNAKE_API ASnakeHead : public APawn
{
	GENERATED_BODY()

public:
	ASnakeHead();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

public:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	FTimerHandle MovementTimerHandle;

	// Movement Values
	float MoveStepSize;

	FVector MoveDirection;
	
private:
	// Movement Methods
	UFUNCTION()
	void MoveSnake();

	void MoveUp();

	void MoveDown();

	void MoveLeft();

	void MoveRight();

private:
	// Snake Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* RootComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* HeadMesh;

private:
	// Defaults
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TSubclassOf<class ATail> DefaultTailClass;

private:
	// Snake tail array
	TArray<class ATail*> Tails;

public:
	// Snake tail methods
	void SpawnTail();

private:
	class ASnakeGameModeBase* GameMode = nullptr;
	
private:
	// Conditions
	bool bIsAlive;

	bool bIsMoving;

public:
	// Conditions methods
	void SetIsAlive(bool inBIsAlive);

private:
	// Audio
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* MoveUpSoundCue = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* MoveDownSoundCue = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* MoveLeftSoundCue = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* MoveRightSoundCue = nullptr;
};
