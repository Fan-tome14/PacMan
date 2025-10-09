#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TestAIController.generated.h"

UCLASS()
class PACMAN_API ATestAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATestAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;
};
