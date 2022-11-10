#include "Wall.h"

AWall::AWall()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshForMesh(TEXT("/Game/Snake/Material/SM_Arena"));
	if (MeshForMesh.Succeeded())
	{
		Mesh->SetStaticMesh(MeshForMesh.Object);
		Mesh->SetRelativeScale3D(FVector(1) / MeshForMesh.Object->GetBoundingBox().GetSize());
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> plane_material(TEXT("/Game/Snake/Material/M_Wall"));
	if (plane_material.Succeeded())
	{
		Mesh->SetMaterial(0, plane_material.Object);
	}
}
