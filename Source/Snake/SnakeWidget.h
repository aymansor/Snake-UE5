#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SnakeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API USnakeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USnakeWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	void UpdateCurrentScoreCount(int Value);
	void UpdateHighestScoreCount(int Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTCurrentScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTHighestScore;
};
