#include "Ghost.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyPacMan.h"
#include "MyGameInstance.h"
#include "GameFramework/FloatingPawnMovement.h"

AGhost::AGhost()
{
    PrimaryActorTick.bCanEverTick = true;

    IsDead = false;
    IsFrightened = false;
    IsNormal = true;

    // BoxCollision
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->SetBoxExtent(FVector(80.f, 80.f, 80.f));
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetGenerateOverlapEvents(true);
    CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);

    // Bind overlap
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnBeginOverlap);

    // PawnMovement
    if (!PawnMovement)
    {
        PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
    }
    PawnMovement->UpdatedComponent = RootComponent;
    PawnMovement->MaxSpeed = 350.f;

    // Flipbook
    if (!Flipbook)
    {
        Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
        Flipbook->SetupAttachment(RootComponent);
    }
    Flipbook->SetLooping(true);
    Flipbook->Play();

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();
}

void AGhost::BeginPlay()
{
    Super::BeginPlay();

    if (BaseFlipbook && Flipbook)
        Flipbook->SetFlipbook(BaseFlipbook);

    if (TreeAsset)
    {
        if (AAIController* AIController = Cast<AAIController>(GetController()))
        {
            AIController->RunBehaviorTree(TreeAsset);
        }
    }

    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if (AICon->GetBlackboardComponent())
            AICon->GetBlackboardComponent()->SetValueAsBool("IsNormal", true);
    }
}

void AGhost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(bCanMove)
        UpdateFlipbookFromVelocity();
}

// --- États ---
void AGhost::SetAliveMode()
{
    IsDead = false;
    IsFrightened = false;
    IsNormal = true;
    bCanMove = true;

    if (BaseFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(BaseFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if (AICon->GetBlackboardComponent())
        {
            AICon->GetBlackboardComponent()->SetValueAsBool("IsNormal", true);
            AICon->GetBlackboardComponent()->ClearValue("IsFrightened");
            AICon->GetBlackboardComponent()->ClearValue("IsDead");
        }
    }
}

void AGhost::SetDeadMode()
{
    IsDead = true;
    IsNormal = false;
    IsFrightened = false;
    
    bCanMove = false; // stop le mouvement immédiatement
    if(PawnMovement)
        PawnMovement->StopMovementImmediately();

    if(DeadFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(DeadFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    // Blackboard
    if(AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if(UBlackboardComponent* BB = AICon->GetBlackboardComponent())
        {
            BB->SetValueAsBool("IsDead", true);
            BB->ClearValue("IsNormal");
            BB->ClearValue("IsFrightened");
        }
    }
}



void AGhost::SetFrightenMode()
{
    IsFrightened = true;
    IsDead = false;
    IsNormal = false;

    if (FrightenFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(FrightenFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if (AICon->GetBlackboardComponent())
        {
            AICon->GetBlackboardComponent()->ClearValue("IsNormal");
            AICon->GetBlackboardComponent()->SetValueAsBool("IsFrightened", true);
        }
    }
}

void AGhost::Respawn()
{
    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if (UBlackboardComponent* BB = AICon->GetBlackboardComponent())
        {
            FVector SpawnLoc = BB->GetValueAsVector("RespawnPoint");
            SetActorLocation(SpawnLoc);
        }
    }
    GetWorldTimerManager().SetTimer(FrightenedTimerHandle, this, &AGhost::SetAliveMode, 5.f, false);
}

// --- Collision ---
void AGhost::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                            bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    if (AMyPacMan* Pac = Cast<AMyPacMan>(OtherActor))
    {
        if (IsDead) return;

        if (IsFrightened)
        {
            SetDeadMode();
            UE_LOG(LogTemp, Warning, TEXT("%s a été mangé par Pac-Man !"), *GetName());
        }
        else if (IsNormal)
        {
            if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
            {
                GI->LoseLife();
            }
            UE_LOG(LogTemp, Warning, TEXT("Pac-Man touché par %s !"), *GetName());
        }
    }
}

// --- Flipbook ---
void AGhost::UpdateFlipbookFromVelocity()
{
    if (!Flipbook || !PawnMovement || !PawnMovement->UpdatedComponent) return;

    FVector Vel = GetVelocity();
    if (Vel.IsNearlyZero()) return;

    FVector Dir = Vel.GetSafeNormal2D();

    if (Dir.Equals(FVector::RightVector, 0.1f))
        Flipbook->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    else if (Dir.Equals(-FVector::RightVector, 0.1f))
        Flipbook->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    else if (Dir.Equals(FVector::ForwardVector, 0.1f))
        Flipbook->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    else if (Dir.Equals(-FVector::ForwardVector, 0.1f))
        Flipbook->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}
