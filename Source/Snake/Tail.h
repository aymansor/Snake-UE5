#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tail.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API ATail : public AActor
{
	GENERATED_BODY()
	
public:
	ATail();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* RootComp;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh;

	virtual void BeginPlay() override;

};
