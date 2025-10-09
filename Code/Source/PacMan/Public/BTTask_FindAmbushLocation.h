#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindAmbushLocation.generated.h"

UCLASS()
class PACMAN_API UBTTask_FindAmbushLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindAmbushLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	// Blackboard key pour la cible à atteindre
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetLocationKey;

	// Distance d'anticipation (combien de cases devant Pac-Man)
	UPROPERTY(EditAnywhere, Category = "Ambush")
	float PredictionDistance = 300.f;
};
