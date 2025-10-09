#include "PacMan/Public/BTTask_FindFrightenedPosition.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PacMan/PacEntity.h"
#include "PacMan/Ghost.h"
#include "EngineUtils.h"

UBTTask_FindFrightenedPosition::UBTTask_FindFrightenedPosition()
{
	NodeName = "Find Frightened Position";
}

EBTNodeResult::Type UBTTask_FindFrightenedPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APawn* Pawn = AICon->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Pawn->GetWorld());
	if (!NavSys) return EBTNodeResult::Failed;

	// Récupérer Pac-Man
	APacEntity* Player = nullptr;
	for (TActorIterator<APacEntity> It(Pawn->GetWorld()); It; ++It)
	{
		Player = *It;
		break;
	}
	if (!Player) return EBTNodeResult::Failed;

	// Chercher une position aléatoire éloignée de Pac-Man
	const int MaxTries = 10;
	FNavLocation RandomLoc;

	for (int i = 0; i < MaxTries; i++)
	{
		if (NavSys->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), Radius, RandomLoc))
		{
			if (FVector::DistSquared(RandomLoc.Location, Player->GetActorLocation()) >= MinDistanceFromPlayer * MinDistanceFromPlayer)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, RandomLoc.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
