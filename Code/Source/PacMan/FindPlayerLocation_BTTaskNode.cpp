#include "FindPlayerLocation_BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

UFindPlayerLocation_BTTaskNode::UFindPlayerLocation_BTTaskNode()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	// Récupérer le joueur
	AActor* Player = UGameplayStatics::GetPlayerPawn(Pawn->GetWorld(), 0);
	if (Player)
	{
		FVector PlayerLocation = Player->GetActorLocation();

		// Mettre la position dans le Blackboard (clé de type Vector)
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), PlayerLocation);

		UE_LOG(LogTemp, Warning, TEXT("Player found at location: X=%f Y=%f Z=%f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);

		return EBTNodeResult::Succeeded;
	}

	UE_LOG(LogTemp, Warning, TEXT("Player introuvable !"));
	return EBTNodeResult::Failed;
}
