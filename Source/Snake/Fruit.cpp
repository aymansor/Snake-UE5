#include "Fruit.h"

#include "SnakeHead.h"
#include "SnakeGameModeBase.h"
#include "Tail.h"

AFruit::AFruit()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECC_Pawn);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AFruit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	Destroy();
	
	if (OtherActor->IsA(ATail::StaticClass()))
	{

		ASnakeGameModeBase* GameMode = Cast<ASnakeGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->SpawnFruit();
		}
	}
}

void AFruit::OverlapedWithSnakeHead(ASnakeHead* SnakeHead)
{
	Destroy();
	ASnakeGameModeBase* GameMode = Cast<ASnakeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnSnakeOverlapFruit();
	}
}

