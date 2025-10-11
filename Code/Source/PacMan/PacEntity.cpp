#include "PacEntity.h"

#include "AIController.h"
#include "TestAIController.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"

APacEntity::APacEntity()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // Flipbook
    Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
    Flipbook->SetupAttachment(RootComponent);
    Flipbook->SetRelativeRotation(FRotator(0.f, 0.f, -90.f)); // horizontal
    Flipbook->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

    // Mouvement
    PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
    PawnMovement->UpdatedComponent = RootComponent;

    // Variables
    MoveSpeed = 300.f;
    DirectionCourante = FVector::ForwardVector;
    ProchaineDirection = FVector::ZeroVector;

    InitialLocation=GetActorLocation();
}

void APacEntity::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("PacEntity prêt !"));
}

void APacEntity::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Changement de direction si possible
    if (!ProchaineDirection.IsZero() && PeutAller(ProchaineDirection))
    {
        DirectionCourante = ProchaineDirection;
        ProchaineDirection = FVector::ZeroVector;
    }

    // Déplacement
    AddMovementInput(DirectionCourante, MoveSpeed * DeltaTime);
}

void APacEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APacEntity::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APacEntity::MoveRight);
}

void APacEntity::MoveForward(float Value)
{
    if (Value == 0.f) return;
    FVector Dir = FVector::ForwardVector * FMath::Sign(Value);

    if (PeutAller(Dir))
        DirectionCourante = Dir;
    else
        ProchaineDirection = Dir;
}

void APacEntity::MoveRight(float Value)
{
    if (Value == 0.f) return;
    FVector Dir = FVector::RightVector * FMath::Sign(Value);

    if (PeutAller(Dir))
        DirectionCourante = Dir;
    else
        ProchaineDirection = Dir;
}

bool APacEntity::PeutAller(const FVector& Direction)
{
    return true; // Pour l’instant toujours possible
}

void APacEntity::ResetPosition()
{
    SetActorLocation(InitialLocation);

    // Si le fantôme a un AIController, reset la navigation
    ATestAIController* AICon = Cast<ATestAIController>(GetController());
    if (AICon)
    {
        AICon->StopMovement(); // Arrête le mouvement en cours
    }
}

