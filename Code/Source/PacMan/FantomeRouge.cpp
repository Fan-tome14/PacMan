#include "FantomeRouge.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "MyPacMan.h"

AFantomeRouge::AFantomeRouge()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    // Cube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
        Mesh->SetStaticMesh(CubeMesh.Object);

    // Matériau rouge
    static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Material/rouge.rouge'"));
    if (Materiau.Succeeded())
        Mesh->SetMaterial(0, Materiau.Object);
}

void AFantomeRouge::BeginPlay()
{
    Super::BeginPlay();
    PacMan = Cast<AMyPacMan>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPacMan::StaticClass()));
}

void AFantomeRouge::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PacMan)
    {
        FVector Direction = (PacMan->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime, true);
    }
}
