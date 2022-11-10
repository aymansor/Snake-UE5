#pragma once

#include "CoreMinimal.h"
#include "Trigerable.h"
#include "Fruit.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API AFruit : public ATrigerable
{
	GENERATED_BODY()

public:
	AFruit();

public:
	void OverlapedWithSnakeHead(class ASnakeHead* SnakeHead) override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
