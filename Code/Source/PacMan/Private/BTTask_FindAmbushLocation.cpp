#include "BTTask_FindAmbushLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PacMan/MyPacMan.h"
#include "GameFramework/Actor.h"

UBTTask_FindAmbushLocation::UBTTask_FindAmbushLocation()
{
	NodeName = "Find Ambush Location";
}

EBTNodeResult::Type UBTTask_FindAmbushLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon)
		return EBTNodeResult::Failed;

	// Trouve Pac-Man dans le niveau
	class AActor* PacManPawn = UGameplayStatics::GetActorOfClass(AICon->GetWorld(), AMyPacMan::StaticClass());
	if (!PacManPawn)
		return EBTNodeResult::Failed;

	FVector PacManPos = PacManPawn->GetActorLocation();
	FVector PacManForward = PacManPawn->GetActorForwardVector();

	// Calcule la position anticipée
	FVector AmbushPos = PacManPos + PacManForward * PredictionDistance;

	// Envoie cette position au Blackboard
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, AmbushPos);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
