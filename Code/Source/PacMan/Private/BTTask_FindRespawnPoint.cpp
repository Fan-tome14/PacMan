#include "PacMan/Public/BTTask_FindRespawnPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "PacMan/Ghost.h"

UBTTask_FindRespawnPoint::UBTTask_FindRespawnPoint()
{
	NodeName = "Find Respawn Point";
}

EBTNodeResult::Type UBTTask_FindRespawnPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	AGhost* Ghost = Cast<AGhost>(AICon->GetPawn());
	if (!Ghost) return EBTNodeResult::Failed;

	for (TActorIterator<AActor> It(Ghost->GetWorld(), RespawnPointClass); It; ++It)
	{
		AActor* RespawnPoint = *It;
		if (RespawnPoint)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, RespawnPoint->GetActorLocation());
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
