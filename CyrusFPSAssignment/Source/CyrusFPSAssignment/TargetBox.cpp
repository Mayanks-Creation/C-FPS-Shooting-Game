#include "TargetBox.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

ATargetBox::ATargetBox()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CubeMesh.Succeeded())
	{
		BoxMesh->SetStaticMesh(CubeMesh.Object);
	}

	// Load material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Materials/M_BoxColor.M_BoxColor"));

	if (Material.Succeeded())
	{
		BoxMesh->SetMaterial(0, Material.Object);
	}

	Health = 3;
	Score = 10;
}
void ATargetBox::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATargetBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ATargetBox::TakeBoxDamage(int32 DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0)
	{
		int32 BoxScore = Score;

		Destroy();

		return BoxScore;
	}
	else
	{
		return 0;
	}
}

void ATargetBox::SetBoxColor(FColor NewColor)
{
	if (BoxMesh)
	{
		UMaterialInstanceDynamic* DynMaterial = BoxMesh->CreateAndSetMaterialInstanceDynamic(0);

		if (DynMaterial)
		{
			DynMaterial->SetVectorParameterValue("BoxColor", FLinearColor(NewColor));
		}
	}
	
}