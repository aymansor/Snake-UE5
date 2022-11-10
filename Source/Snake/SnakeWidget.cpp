#include "SnakeWidget.h"
#include "Components/TextBlock.h"

USnakeWidget::USnakeWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (TXTCurrentScore)
	{
		TXTCurrentScore->SetVisibility(ESlateVisibility::Visible);
	}

	if (TXTHighestScore)
	{
		TXTHighestScore->SetVisibility(ESlateVisibility::Visible);
	}

}

void USnakeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USnakeWidget::UpdateCurrentScoreCount(int Value)
{
	if (TXTCurrentScore)
	{
		TXTCurrentScore->SetText(FText::FromString("Score: " + FString::FromInt(Value)));
	}
	
}

void USnakeWidget::UpdateHighestScoreCount(int Value)
{
	if (TXTHighestScore)
	{
		TXTHighestScore->SetText(FText::FromString("Highest: " + FString::FromInt(Value)));
	}
	
}
