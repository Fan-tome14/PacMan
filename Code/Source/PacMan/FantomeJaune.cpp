#include "FantomeJaune.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPacMan.h"

AFantomeJaune::AFantomeJaune()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
        Mesh->SetStaticMesh(CubeMesh.Object);

    static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Material/jaune.jaune'"));
    if (Materiau.Succeeded())
        Mesh->SetMaterial(0, Materiau.Object);
}

void AFantomeJaune::BeginPlay()
{
    Super::BeginPlay();
    PacMan = Cast<AMyPacMan>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPacMan::StaticClass()));
}

void AFantomeJaune::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PacMan)
    {
        float Distance = FVector::Dist(GetActorLocation(), PacMan->GetActorLocation());

        if (Distance > 200.f)
            Direction = (PacMan->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        else
            Direction = (GetActorLocation() - PacMan->GetActorLocation()).GetSafeNormal();

        SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime, true);
    }
}
