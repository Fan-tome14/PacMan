// BTTask_UpdateTricksterTarget.cpp
#include "BTTask_UpdateTricksterTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "PacMan/MyPacMan.h"
#include "Blinky.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

UBTTask_UpdateTricksterTarget::UBTTask_UpdateTricksterTarget()
{
    NodeName = "Update Trickster Target";
}

EBTNodeResult::Type UBTTask_UpdateTricksterTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) return EBTNodeResult::Failed;

    AGhost* Trickster = Cast<AGhost>(AICon->GetPawn());
    if (!Trickster) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return EBTNodeResult::Failed;

    AMyPacMan* Player = Cast<AMyPacMan>(UGameplayStatics::GetActorOfClass(Trickster->GetWorld(), AMyPacMan::StaticClass()));
    if (!Player) return EBTNodeResult::Failed;

    ABlinky* Blinky = Cast<ABlinky>(UGameplayStatics::GetActorOfClass(Trickster->GetWorld(), ABlinky::StaticClass()));

    FVector TargetLoc;

    if (Blinky)
    {
        // 2 cases devant Pac-Man
        FVector PacFront = Player->GetActorLocation() + Player->GetActorForwardVector() * (2 * TileSize);

        // Vecteur vers Blinky
        FVector Vec = PacFront - Blinky->GetActorLocation();

        // Target finale pour Trickster (Inky)
        TargetLoc = Blinky->GetActorLocation() + Vec * 2;
    }
    else
    {
        TargetLoc = Player->GetActorLocation();
    }

    // ⚡ S'assurer que la target reste sur le NavMesh
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Trickster->GetWorld());
    if (NavSys)
    {
        FNavLocation NavLoc;
        if (NavSys->ProjectPointToNavigation(TargetLoc, NavLoc, FVector(MaxNavOffset, MaxNavOffset, MaxNavOffset)))
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, NavLoc.Location);

        }
        else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, Player->GetActorLocation());
        }
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
