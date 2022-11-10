#include "Trigerable.h"
#include "SnakeHead.h"

ATrigerable::ATrigerable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ATrigerable::BeginPlay()
{
	Super::BeginPlay();

}

void ATrigerable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrigerable::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ASnakeHead* OverlapedActorAsSnakeHead = Cast<ASnakeHead>(OtherActor);

	if (OverlapedActorAsSnakeHead)
	{
		OverlapedWithSnakeHead(OverlapedActorAsSnakeHead);
	}
}

