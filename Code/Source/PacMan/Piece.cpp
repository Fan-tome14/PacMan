#include "Piece.h"

APiece::APiece()
{
    PrimaryActorTick.bCanEverTick = true;
    MeshPiece = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPiece"));
    SetRootComponent(MeshPiece);
    MeshPiece->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Cube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshPiece->SetStaticMesh(CubeMesh.Object);
    }

    // Matériau (par exemple jaune)
    static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Material/jaune.jaune'"));
    if (Materiau.Succeeded())
    {
        MeshPiece->SetMaterial(0, Materiau.Object);
    }
}


void APiece::BeginPlay()
{
	Super::BeginPlay();
}

void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
