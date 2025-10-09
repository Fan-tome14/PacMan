#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRespawnPoint.generated.h"

UCLASS()
class PACMAN_API UBTTask_FindRespawnPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindRespawnPoint();

	/** Classe des points de respawn à rechercher dans le niveau */
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> RespawnPointClass;

	/** Clé du Blackboard pour stocker la position cible */
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetLocationKey;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
