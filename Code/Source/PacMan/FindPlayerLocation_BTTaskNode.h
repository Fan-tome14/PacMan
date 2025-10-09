#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindPlayerLocation_BTTaskNode.generated.h"

/**
 * Tâche BT : récupérer la position du joueur
 */
UCLASS()
class PACMAN_API UFindPlayerLocation_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindPlayerLocation_BTTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
