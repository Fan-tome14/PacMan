#include "FantomeRose.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "MyPacMan.h"

AFantomeRose::AFantomeRose()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
        Mesh->SetStaticMesh(CubeMesh.Object);

    static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Material/rose.rose'"));
    if (Materiau.Succeeded())
        Mesh->SetMaterial(0, Materiau.Object);
}

void AFantomeRose::BeginPlay()
{
    Super::BeginPlay();
    PacMan = Cast<AMyPacMan>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPacMan::StaticClass()));
}

void AFantomeRose::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PacMan)
    {
        FVector Forward = PacMan->GetActorForwardVector() * 300.f;
        FVector Target = PacMan->GetActorLocation() + Forward;
        FVector Direction = (Target - GetActorLocation()).GetSafeNormal();
        SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime, true);
    }
}
