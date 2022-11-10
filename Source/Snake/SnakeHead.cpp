#include "SnakeHead.h"
#include "Tail.h"
#include "Snake/SnakeGameModeBase.h"

ASnakeHead::ASnakeHead()
{
	// set tick
	PrimaryActorTick.bCanEverTick = false;

	// set root component
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	// set mesh
	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(RootComp);
	HeadMesh->SetRelativeScale3D(FVector(0.9f));
	HeadMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HeadMesh->SetCollisionObjectType(ECC_Pawn);
	HeadMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	// set movement
	MoveDirection = FVector(0.0f);
	MoveStepSize = 0.0f;
	bIsMoving = false;
	bIsAlive = true;
}

void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &ASnakeHead::MoveUp);
		PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ASnakeHead::MoveDown);
		PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASnakeHead::MoveLeft);
		PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ASnakeHead::MoveRight);
	}
}

void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ASnakeGameModeBase>(GetWorld()->GetAuthGameMode());
	check(GameMode);

	MoveStepSize = HeadMesh->GetStaticMesh()->GetBoundingBox().GetSize().X;

	// Looping timer for the snake movement
	FTimerHandle TimerHandle_AttackDelay;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "MoveSnake");

	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, Delegate, 0.15f, true);
}

void ASnakeHead::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(ATail::StaticClass()))
	{
		if (GameMode && !GameMode->bIsGodModeEnabled)
		{
			UE_LOG(LogTemp, Warning, TEXT("Snake overlapped tail"));
			SetIsAlive(false);
			GameMode->StopPlayingMusic();
			GameMode->GameOver();
		}
	}
}

void ASnakeHead::MoveSnake()
{
	if (!bIsAlive)
	{
		// Clear timer when the snake dies
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		return;
	}

	// Move Snake Head
	FVector OldLocation = HeadMesh->GetComponentLocation();
	FRotator OldRotation = HeadMesh->GetComponentRotation();

	AddActorWorldOffset(MoveDirection * MoveStepSize);
	bIsMoving = true;

	// Move Snake Tail
	for (int i = 0; i < Tails.Num(); i++)
	{
		FVector CurrentLocation = Tails[i]->GetActorLocation();
		FRotator CurrentRotation = Tails[i]->GetActorRotation();

		Tails[i]->SetActorLocation(OldLocation);
		Tails[i]->SetActorRotation(OldRotation);

		OldLocation = CurrentLocation;
		OldRotation = CurrentRotation;
	}
}

void ASnakeHead::MoveUp()
{
	if (MoveDirection.X == 0.0 && bIsMoving)
	{
		bIsMoving = false;
		MoveDirection = FVector(1.0, 0.0, 0.0);
		SetActorRotation(FRotator(0.0, 0.0, 0.0));

		GameMode->PlaySound(MoveUpSoundCue);
	}
}

void ASnakeHead::MoveDown()
{
	if (MoveDirection.X == 0.0 && bIsMoving)
	{
		bIsMoving = false;
		MoveDirection = FVector(-1.0, 0.0, 0.0);
		SetActorRotation(FRotator(0.0, 180.0, 0.0));
		
		GameMode->PlaySound(MoveDownSoundCue);
	}
}

void ASnakeHead::MoveLeft()
{
	if (MoveDirection.Y == 0.0 && bIsMoving)
	{
		bIsMoving = false;
		MoveDirection = FVector(0.0, -1.0, 0.0);
		SetActorRotation(FRotator(0.0, -90.0, 0.0));
		
		GameMode->PlaySound(MoveLeftSoundCue);
	}
}

void ASnakeHead::MoveRight()
{
	if (MoveDirection.Y == 0.0 && bIsMoving)
	{
		bIsMoving = false;
		MoveDirection = FVector(0.0, 1.0, 0.0);
		SetActorRotation(FRotator(0.0, 90.0, 0.0));
		
		GameMode->PlaySound(MoveRightSoundCue);
	}
}

void ASnakeHead::SpawnTail()
{
	const FVector TailSpawnLocation = (Tails.IsEmpty() ? HeadMesh->GetComponentLocation() : Tails.Last()->GetActorLocation()) - (MoveDirection * MoveStepSize);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ATail* NewTail = GetWorld()->SpawnActor<ATail>(DefaultTailClass, TailSpawnLocation, FRotator(), SpawnParams);

	if (NewTail)
	{
		Tails.Add(NewTail);
	}
}

void ASnakeHead::SetIsAlive(bool inBIsAlive)
{
	bIsAlive = inBIsAlive;
}
