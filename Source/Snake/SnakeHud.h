#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SnakeHud.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API ASnakeHud : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	// Defaults - Assigned in blueprints
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> SnakeWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> SettingsWidgetClass;

private:
	// Widgets references
	class USnakeWidget* SnakeWidget = nullptr;

	class UGameOver* GameOverWidget = nullptr;

	class UPauseMenu* PauseMenuWidget = nullptr;

	class USettingsMenu* SettingsWidget = nullptr;

private:
	// Initialize menu widgets
	void CreateSnakeWidget();

	void CreatePauseMenuWidget();

	void CreateSettingsMenuWidget();

public:
	// Public widget methods
	UFUNCTION()
	void UpdateCurrentScore(int Value);
	
	UFUNCTION()
	void UpdateHighestScore(int Value);

	UFUNCTION()
	void ShowGameOverWidget();

	UFUNCTION()
	void ShowPauseMenuWidget();

	UFUNCTION()
	void HidePauseMenuWidget();

	UFUNCTION()
	void ShowSettingsMenuWidget();

	UFUNCTION()
	void HideSettingsMenuWidget();
};
