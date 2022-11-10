#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASnakePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API AASnakePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

private:
	bool bPauseMenuVisible = false;

	bool bSettingsMenuVisible = false;

	class ASnakeHud* SnakeHud = nullptr;

public:
	void TogglePauseMenu();

	void ToggleSettingsMenu();

	void ToggleGameOverMenu();

	void ClearScore();
};
