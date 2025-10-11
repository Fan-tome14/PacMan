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

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnBeginOverlap);

    // PawnMovement
    if (!PawnMovement)
    {
        PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
    }
    PawnMovement->UpdatedComponent = RootComponent;
    PawnMovement->MaxSpeed = 350.f;
    
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
    
    bCanMove = false;
    if(PawnMovement)
        PawnMovement->StopMovementImmediately();

    if(DeadFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(DeadFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

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
    bCanMove = true;

    if (FrightenFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(FrightenFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if (UBlackboardComponent* BB = AICon->GetBlackboardComponent())
        {
            BB->ClearValue("IsNormal");
            BB->SetValueAsBool("IsFrightened", true);
        }
    }

    // Timer pour finir le frightened mode
    GetWorldTimerManager().SetTimer(FrightenedTimerHandle, this, &AGhost::EndFrightenedMode, 5.f, false);
}

void AGhost::EndFrightenedMode()
{
    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        if (UBlackboardComponent* BB = AICon->GetBlackboardComponent())
        {
            BB->ClearValue("IsFrightened");
            BB->SetValueAsBool("IsNormal", true);
        }
        SetAliveMode();
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
    if (!OtherActor || OtherActor == this) 
        return;

    AMyPacMan* Pac = Cast<AMyPacMan>(OtherActor);
    if (!Pac) return;

    AAIController* AICon = Cast<AAIController>(GetController());
    if (!AICon) return;

    UBlackboardComponent* BB = AICon->GetBlackboardComponent();
    if (!BB) return;

    bool bIsDead = BB->GetValueAsBool("IsDead");
    bool bIsFrightened = BB->GetValueAsBool("IsFrightened");
    bool bIsNormal = BB->GetValueAsBool("IsNormal");

    if (bIsDead) 
        return;

    if (bIsFrightened)
    {
        SetDeadMode();
        UE_LOG(LogTemp, Warning, TEXT("%s a été mangé par Pac-Man !"), *GetName());
    }
    else if (bIsNormal)
    {
        if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
        {
            GI->LoseLife();
        }
        UE_LOG(LogTemp, Warning, TEXT("Pac-Man touché par %s !"), *GetName());
    }
}
void AGhost::ResetGhost()
{
    // jsute pour debug
}
// --- Flipbook ---
void AGhost::UpdateFlipbookFromVelocity()
{
    if (!Flipbook || !PawnMovement || !PawnMovement->UpdatedComponent) return;

    FVector Vel = GetVelocity();
    if (Vel.IsNearlyZero()) return;

    FVector Dir = Vel.GetSafeNormal2D();

    // Détermination de la direction dominante
    if (FMath::Abs(Dir.X) > FMath::Abs(Dir.Y))
    {
        // Gauche / Droite
        if (Dir.X > 0.1f)
        {
            if (Flipbook_Right) Flipbook->SetFlipbook(Flipbook_Right);
            Flipbook->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
        }
        else if (Dir.X < -0.1f)
        {
            if (Flipbook_Left) Flipbook->SetFlipbook(Flipbook_Left);
            Flipbook->SetRelativeRotation(FRotator(0.f, 180.f, -90.f));
        }
    }
    else
    {
        // Haut / Bas
        if (Dir.Y > 0.1f)
        {
            if (Flipbook_Up) Flipbook->SetFlipbook(Flipbook_Up);
            Flipbook->SetRelativeRotation(FRotator(0.f, -90.f, -90.f));
        }
        else if (Dir.Y < -0.1f)
        {
            if (Flipbook_Down) Flipbook->SetFlipbook(Flipbook_Down);
            Flipbook->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));
        }
    }

    Flipbook->SetLooping(true);
    Flipbook->Play();
}

