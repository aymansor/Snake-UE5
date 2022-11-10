#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Arena.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE_API AArena : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AArena();
	void BeginPlay() override;
	void GetRandomFruitSpawnLocation(FVector& OutLocation);

private:
	void SpawnWall(FVector SpawnLocation, FVector SpawnScale);

private:
	float WallWidth;
	float WallHeight;

public:

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UMaterialInterface* ArenaGameOverMaterial;
};
