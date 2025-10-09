#include "MyPacMan.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/FloatingPawnMovement.h"

AMyPacMan::AMyPacMan()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root vide
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    SetRootComponent(RootScene);

    // Collision principale
    CollisionPacMan = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    CollisionPacMan->SetBoxExtent(FVector(85.f, 85.f, 85.f));
    CollisionPacMan->SetCollisionProfileName(TEXT("Pawn"));
    CollisionPacMan->SetupAttachment(RootScene);
    
    // Flipbook
    Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
    Flipbook->SetupAttachment(RootScene);
    Flipbook->SetRelativeRotation(FRotator(0.f, 0.f, -90.f)); // tourne autour de Z pour l’horizontalité
    Flipbook->SetRelativeLocation(FVector(0.f, 0.f, 50.f));   // au-dessus du sol

    // Mouvement
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
    {
        AddMovementInput(DirectionCourante, 1.f);
        UpdateFlipbookRotation();
    }
    else
    {
        DirectionCourante = FVector::ZeroVector;
    }
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

void AMyPacMan::UpdateFlipbookRotation()
{
    if (!Flipbook) return;

    // Rotation de base : à plat
    FRotator BaseRotation(0.f, 0.f, -90.f); // met le flipbook horizontal

    FVector Dir = DirectionCourante.GetSafeNormal2D();
    float Yaw = 0.f;

    if (Dir.Equals(FVector::RightVector, 0.1f))        // droite
        Yaw = 0.f;
    else if (Dir.Equals(-FVector::RightVector, 0.1f))  // gauche
        Yaw = 180.f;
    else if (Dir.Equals(FVector::ForwardVector, 0.1f)) // haut
        Yaw = -90.f;
    else if (Dir.Equals(-FVector::ForwardVector, 0.1f))// bas
        Yaw = 90.f;

    BaseRotation.Yaw = Yaw;
    Flipbook->SetRelativeRotation(BaseRotation);
}
