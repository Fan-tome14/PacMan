#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindFrightenedPosition.generated.h"

UCLASS()
class PACMAN_API UBTTask_FindFrightenedPosition : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindFrightenedPosition();

	// Blackboard key pour MoveTo
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector TargetLocation;

	// Distance minimum par rapport à Pac-Man
	UPROPERTY(EditAnywhere, Category="AI")
	float MinDistanceFromPlayer = 300.f;

	// Rayon maximum pour la position aléatoire
	UPROPERTY(EditAnywhere, Category="AI")
	float Radius = 500.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
