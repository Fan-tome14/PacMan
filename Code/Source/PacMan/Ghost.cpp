#include "Ghost.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PacEntity.h"
#include "BehaviorTree/BlackboardComponent.h"

AGhost::AGhost()
{
    PrimaryActorTick.bCanEverTick = true;

    IsDead = false;
    IsFrightened = false;
    IsNormal = true;

    PawnMovement->MaxSpeed = 350.f;

    if (Flipbook)
    {
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();
}

void AGhost::BeginPlay()
{
    Super::BeginPlay();

    if (BaseFlipbook && Flipbook)
        Flipbook->SetFlipbook(BaseFlipbook);

    OnActorBeginOverlap.AddDynamic(this, &AGhost::OnOverlap);

    if (TreeAsset)
    {
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
            AIController->RunBehaviorTree(TreeAsset);
    }
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon && AICon->GetBlackboardComponent())
        AICon->GetBlackboardComponent()->SetValueAsBool("IsNormal", true);
}

void AGhost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateFlipbookFromVelocity();
}

// --- États ---
void AGhost::SetAliveMode()
{
    IsDead = false;
    IsFrightened = false;
    IsNormal = true;

    if (BaseFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(BaseFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    UE_LOG(LogTemp, Log, TEXT("%s est maintenant normal."), *GetName());

    // Blackboard : IsNormal set, IsFrightened cleared
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon && AICon->GetBlackboardComponent())
    {
        AICon->GetBlackboardComponent()->SetValueAsBool("IsNormal", true);
        AICon->GetBlackboardComponent()->ClearValue("IsFrightened");
    }
}

void AGhost::SetDeadMode()
{
    IsDead = true;
    IsFrightened = false;
    IsNormal = false;

    if (DeadFlipbook && Flipbook)
    {
        Flipbook->SetFlipbook(DeadFlipbook);
        Flipbook->SetLooping(true);
        Flipbook->Play();
    }

    UE_LOG(LogTemp, Log, TEXT("%s est mort."), *GetName());

    // Blackboard : clear IsNormal
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon && AICon->GetBlackboardComponent())
        AICon->GetBlackboardComponent()->ClearValue("IsNormal");
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

    UE_LOG(LogTemp, Log, TEXT("%s est effrayé !"), *GetName());

    // Blackboard
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon && AICon->GetBlackboardComponent())
    {
        AICon->GetBlackboardComponent()->ClearValue("IsNormal");
        AICon->GetBlackboardComponent()->SetValueAsBool("IsFrightened", true);
    }

    // Lance le timer pour revenir en mode normal
    GetWorldTimerManager().ClearTimer(FrightenedTimerHandle);
    GetWorldTimerManager().SetTimer(FrightenedTimerHandle, this, &AGhost::SetAliveMode, FrightenedDuration, false);
}


// --- Collision ---
void AGhost::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (!OtherActor || OtherActor == this) return;

    APacEntity* Pac = Cast<APacEntity>(OtherActor);
    if (Pac)
    {
        if (IsFrightened)
            SetDeadMode();
        else if (!IsDead)
            UE_LOG(LogTemp, Warning, TEXT("Pac-Man touché par %s !"), *GetName());
    }
}

// --- Flipbook ---
void AGhost::UpdateFlipbookFromVelocity()
{
    if (!Flipbook) return;

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
