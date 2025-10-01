#include "MyPacMan.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Piece.h"
#include "UObject/ConstructorHelpers.h"

AMyPacMan::AMyPacMan()
{
	PrimaryActorTick.bCanEverTick = true;

	ComposantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(ComposantMesh);

	// Ajouter un cube
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		ComposantMesh->SetStaticMesh(CubeMesh.Object);
	}

	// Appliquer un matériau
	static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Material/jaune.jaune'"));
	if (Materiau.Succeeded())
	{
		ComposantMesh->SetMaterial(0, Materiau.Object);
	}

	ComposantMouvement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Mouvement"));
	ComposantMouvement->MaxSpeed = 600.f;

	OnActorBeginOverlap.AddDynamic(this, &AMyPacMan::OnOverlapPiece);
}

void AMyPacMan::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPacMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axes pour ZQSD
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPacMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPacMan::MoveRight);
}

// Déplacement avant/arrière
void AMyPacMan::MoveForward(float Value)
{
	if (Value != 0.f && PeutAller(FVector::ForwardVector * Value))
	{
		AddMovementInput(FVector::ForwardVector, Value);
	}
}

// Déplacement gauche/droite
void AMyPacMan::MoveRight(float Value)
{
	if (Value != 0.f && PeutAller(FVector::RightVector * Value))
	{
		AddMovementInput(FVector::RightVector, Value);
	}
}

bool AMyPacMan::PeutAller(FVector Direction)
{
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = Start + Direction * 100.f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);

	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.f, 0, 2.f);

	return !bHit;
}

void AMyPacMan::OnOverlapPiece(AActor* OverlappedActor, AActor* OtherActor)
{
	APiece* Piece = Cast<APiece>(OtherActor);
	if (Piece)
	{
		Piece->Destroy();
	}
}
