// BTTask_UpdateTricksterTarget.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateTricksterTarget.generated.h"

UCLASS()
class PACMAN_API UBTTask_UpdateTricksterTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_UpdateTricksterTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Taille d'une case pour le calcul devant Pac-Man
	UPROPERTY(EditAnywhere, Category="PacMan")
	float TileSize = 300.f;

	// Distance minimale à respecter pour rester sur le NavMesh
	UPROPERTY(EditAnywhere, Category="PacMan")
	float MaxNavOffset = 100.f;

	// Clé du Blackboard pour la target
	UPROPERTY(EditAnywhere, Category="PacMan")
	FBlackboardKeySelector TargetLocation;
};
