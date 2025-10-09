#include "PacEntity.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Ghost.h"
#include "MyPacMan.h"

// Sets default values
APacEntity::APacEntity()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root simple
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // Collision box attachée au root
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->SetBoxExtent(FVector(16.f, 16.f, 16.f));
    CollisionBox->SetCollisionProfileName(TEXT("Pawn"));
    CollisionBox->SetGenerateOverlapEvents(true);

    // Bind Overlap
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APacEntity::OnOverlap);

    // Flipbook attaché au root
    Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
    Flipbook->SetupAttachment(RootComponent);

    // Mouvement
    PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
    PawnMovement->UpdatedComponent = RootComponent;

    // Variables
    MoveSpeed = 300.f;
    DirectionCourante = FVector::ForwardVector;
    ProchaineDirection = FVector::ZeroVector;

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APacEntity::OnOverlap);
}

// --- Overlap ---
void APacEntity::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                           bool bFromSweep, const FHitResult & SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    AMyPacMan* Pac = Cast<AMyPacMan>(OtherActor);
    if (!Pac) return;

    AGhost* Ghost = Cast<AGhost>(this);
    if (!Ghost) return;

    if (Ghost->IsNormal)
    {
        if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
        {
            GI->LoseLife();
        }
    }
    // sinon (frightened ou dead) ne rien faire
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

    // Flipbook
    UpdateFlipbookOrientation();
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
    // Pour l’instant, toujours vrai
    return true;
}

void APacEntity::UpdateFlipbookOrientation()
{
    if (!Flipbook) return;

    FVector Dir = DirectionCourante;

    if (Dir.Equals(FVector::RightVector))
        Flipbook->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    else if (Dir.Equals(-FVector::RightVector))
        Flipbook->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    else if (Dir.Equals(FVector::ForwardVector))
        Flipbook->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    else if (Dir.Equals(-FVector::ForwardVector))
        Flipbook->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}
