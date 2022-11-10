#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SnakeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API USnakeSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USnakeSaveGame();

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 SnakeHighestScore;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

};
