#include "MyPacMan.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

AMyPacMan::AMyPacMan()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionPacMan = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionPacMan->SetBoxExtent(FVector(85.f, 85.f, 85.f));
	CollisionPacMan->SetCollisionProfileName(TEXT("Pawn"));
	SetRootComponent(CollisionPacMan);

	ComposantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ComposantMesh->SetupAttachment(CollisionPacMan);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		ComposantMesh->SetStaticMesh(CylinderMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Materiau(TEXT("Material'/Game/Material/jaune.jaune'"));
	if (Materiau.Succeeded())
	{
		ComposantMesh->SetMaterial(0, Materiau.Object);
	}

	ComposantMouvement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Mouvement"));
	ComposantMouvement->MaxSpeed = 600.f;
}

void AMyPacMan::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPacMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!DirectionCourante.IsZero() && PeutAller(DirectionCourante))
		AddMovementInput(DirectionCourante, 1.f);
	else
		DirectionCourante = FVector::ZeroVector;
}

void AMyPacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPacMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPacMan::MoveRight);
}

void AMyPacMan::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		FVector Dir = FVector::ForwardVector * FMath::Sign(Value);
		if (PeutAller(Dir))
			DirectionCourante = Dir;
	}
}

void AMyPacMan::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		FVector Dir = FVector::RightVector * FMath::Sign(Value);
		if (PeutAller(Dir))
			DirectionCourante = Dir;
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
	return !bHit;
}

