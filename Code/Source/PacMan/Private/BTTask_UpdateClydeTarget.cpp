// BTTask_UpdateClydeTarget.cpp
#include "BTTask_UpdateClydeTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "PacMan/MyPacMan.h"
#include "Clyde.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

UBTTask_UpdateClydeTarget::UBTTask_UpdateClydeTarget()
{
    NodeName = "Update Clyde Target";
}

EBTNodeResult::Type UBTTask_UpdateClydeTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) return EBTNodeResult::Failed;

    AClyde* Clyde = Cast<AClyde>(AICon->GetPawn());
    if (!Clyde) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return EBTNodeResult::Failed;

    AMyPacMan* Player = Cast<AMyPacMan>(UGameplayStatics::GetActorOfClass(Clyde->GetWorld(), AMyPacMan::StaticClass()));
    if (!Player) return EBTNodeResult::Failed;

    FVector TargetLoc;
    float DistanceToPlayer = FVector::Dist(Player->GetActorLocation(), Clyde->GetActorLocation());

    if (DistanceToPlayer > MaxDistanceToPacMan)
    {
        // Si Pac-Man est loin, Clyde poursuit
        TargetLoc = Player->GetActorLocation();
    }
    else
    {
        // Si Pac-Man est proche, Clyde se dirige vers son coin gauche
        if (Clyde->LeftCornerActor)
        {
            TargetLoc = Clyde->LeftCornerActor->GetActorLocation();
        }
        else
        {
            // Fallback si le Blueprint n'est pas assigné
            TargetLoc = Clyde->GetActorLocation();
        }
    }

    // ⚡ Projection sur NavMesh pour éviter les bugs
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Clyde->GetWorld());
    if (NavSys)
    {
        FNavLocation NavLoc;
        if (NavSys->ProjectPointToNavigation(TargetLoc, NavLoc, FVector(MaxNavOffset, MaxNavOffset, MaxNavOffset)))
        {
            BB->SetValueAsVector("TargetLocation", NavLoc.Location);
        }
        else
        {
            BB->SetValueAsVector("TargetLocation", Clyde->GetActorLocation());
        }
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
