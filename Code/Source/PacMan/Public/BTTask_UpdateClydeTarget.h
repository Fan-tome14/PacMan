// BTTask_UpdateClydeTarget.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateClydeTarget.generated.h"

UCLASS()
class PACMAN_API UBTTask_UpdateClydeTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_UpdateClydeTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Distance à Pac-Man pour savoir si Clyde fuit ou poursuit
	UPROPERTY(EditAnywhere, Category="PacMan")
	float MaxDistanceToPacMan = 500.f;

	// Distance de projection NavMesh
	UPROPERTY(EditAnywhere, Category="PacMan")
	float MaxNavOffset = 100.f;
};
