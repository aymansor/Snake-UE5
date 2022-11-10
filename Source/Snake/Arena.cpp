#include "Arena.h"
#include "Wall.h"

AArena::AArena()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshForMesh(TEXT("/Game/Snake/Material/SM_Arena"));
	if (MeshForMesh.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshForMesh.Object);
		GetStaticMeshComponent()->SetRelativeScale3D(FVector(1) / MeshForMesh.Object->GetBoundingBox().GetSize());
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> plane_material(TEXT("/Game/Snake/Material/M_ArenaGrid"));
	if (plane_material.Succeeded())
	{
		GetStaticMeshComponent()->SetMaterial(0, plane_material.Object);
	}

	WallHeight = 50;
	WallWidth = 50;
}

void AArena::BeginPlay()
{
	Super::BeginPlay();

	FVector Origin;
	FVector Extend;

	// return values to origin and extend, since passed by reference
	GetActorBounds(false, Origin, Extend);

	FVector LeftWallLoc = Origin - FVector(Extend.X + WallWidth / 2, 0, 0);
	FVector VerticalWallScale = FVector(WallWidth, Extend.Y * 2 , WallHeight);
	SpawnWall(LeftWallLoc, VerticalWallScale);

	FVector RightWallLoc = Origin + FVector(Extend.X + WallWidth / 2, 0, 0);
	SpawnWall(RightWallLoc, VerticalWallScale);


	FVector UpWallLoc = Origin + FVector(0, Extend.Y + WallWidth / 2, 0);
	FVector HorizontalWallScale = FVector(Extend.X * 2 + WallWidth * 2, WallWidth, WallHeight);
	SpawnWall(UpWallLoc, HorizontalWallScale);

	FVector DownWallLoc = Origin - FVector(0, Extend.Y + WallWidth / 2, 0);
	SpawnWall(DownWallLoc, HorizontalWallScale);


}

void AArena::SpawnWall(FVector SpawnLocation, FVector SpawnScale)
{
	FTransform SpawnTransform = FTransform(FRotator(), SpawnLocation, SpawnScale);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(AWall::StaticClass(), SpawnTransform, SpawnParams);
}

void AArena::GetRandomFruitSpawnLocation(FVector& OutLocation)
{
	FVector Origin;
	FVector Extend;
	GetActorBounds(false, Origin, Extend);

	float SpawnZ = Origin.Z + Extend.Z;
	// -/+ WallWidth to avoid spawning fruit clipping with walls
	float SpawnX = FMath::RandRange(Origin.X - Extend.X + WallWidth, Origin.X + Extend.X - WallWidth);
	float SpawnY = FMath::RandRange(Origin.Y - Extend.Y + WallWidth, Origin.Y + Extend.Y - WallWidth);

	OutLocation = FVector(SpawnX, SpawnY, SpawnZ);
}
