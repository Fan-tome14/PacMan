#include "FantomeBleu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "MyPacMan.h"

AFantomeBleu::AFantomeBleu()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
        Mesh->SetStaticMesh(CubeMesh.Object);

    static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Image/bleuMat.bleuMat'"));
    if (Materiau.Succeeded())
        Mesh->SetMaterial(0, Materiau.Object);
}

void AFantomeBleu::BeginPlay()
{
    Super::BeginPlay();
    PacMan = Cast<AMyPacMan>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPacMan::StaticClass()));
}

void AFantomeBleu::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PacMan)
    {
        FVector Direction = (PacMan->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime, true);
    }
}
