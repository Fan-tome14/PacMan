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
	// Override pour posséder le Pawn
	virtual void OnPossess(APawn* InPawn) override;

public:
	// Permet d'assigner Pac-Man comme cible depuis Blueprint ou Level Blueprint
	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* Target);

protected:
	// Composants du Behavior Tree et Blackboard
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBehaviorTreeComponent* BehaviorTreeComponent;
};
