#include "BTTask_SetAliveMode.h"
#include "AIController.h"
#include "PacMan/Ghost.h"

UBTTask_SetAliveMode::UBTTask_SetAliveMode()
{
	NodeName = "Set Alive Mode";
}

EBTNodeResult::Type UBTTask_SetAliveMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	AGhost* Ghost = Cast<AGhost>(AICon->GetPawn());
	if (!Ghost) return EBTNodeResult::Failed;

	Ghost->bCanMove = true;
	Ghost->SetAliveMode();

	return EBTNodeResult::Succeeded;
}
