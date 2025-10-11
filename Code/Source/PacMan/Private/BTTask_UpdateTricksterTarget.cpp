// BTTask_UpdateTricksterTarget.cpp
#include "BTTask_UpdateTricksterTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "PacMan/MyPacMan.h"
#include "Blinky.h"
#include "EngineUtils.h"
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

    // Récupérer Pac-Man via TActorIterator pour plus de sécurité
    AMyPacMan* Player = nullptr;
    for (TActorIterator<AMyPacMan> It(Trickster->GetWorld()); It; ++It)
    {
        Player = *It;
        break;
    }
    if (!Player) return EBTNodeResult::Failed;

    // Récupérer Blinky
    ABlinky* Blinky = nullptr;
    for (TActorIterator<ABlinky> It(Trickster->GetWorld()); It; ++It)
    {
        Blinky = *It;
        break;
    }

    FVector TargetLoc;
    if (Blinky)
    {
        FVector PacFront = Player->GetActorLocation() + Player->GetActorForwardVector() * (2 * TileSize);
        FVector Vec = PacFront - Blinky->GetActorLocation();
        TargetLoc = Blinky->GetActorLocation() + Vec * 2;
    }
    else
    {
        TargetLoc = Player->GetActorLocation();
    }

    // Vérifier que la position est sur le NavMesh
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Trickster->GetWorld());
    if (NavSys)
    {
        FNavLocation NavLoc;
        if (NavSys->ProjectPointToNavigation(TargetLoc, NavLoc, FVector(MaxNavOffset, MaxNavOffset, MaxNavOffset)))
        {
            BB->SetValueAsVector("TargetLocation", NavLoc.Location); // clé hardcodée comme FindFrightened
        }
        else
        {
            BB->SetValueAsVector("TargetLocation", Player->GetActorLocation());
        }

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

