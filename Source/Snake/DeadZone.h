#pragma once

#include "CoreMinimal.h"
#include "Trigerable.h"
#include "DeadZone.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API ADeadZone : public ATrigerable
{
	GENERATED_BODY()

public:
	void OverlapedWithSnakeHead(class ASnakeHead* SnakeHead) override;
};
