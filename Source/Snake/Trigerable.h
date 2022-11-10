#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigerable.generated.h"

class ASnakeHead;

UCLASS()
class SNAKE_API ATrigerable : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrigerable();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* RootComp;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh;

public:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	virtual void OverlapedWithSnakeHead(class ASnakeHead* SnakeHead) PURE_VIRTUAL(ATrigerable::OverlapedWithSnakeHead);
};
