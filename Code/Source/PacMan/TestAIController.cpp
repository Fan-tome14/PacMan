#include "TestAIController.h"

#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPacMan.h"

ATestAIController::ATestAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void ATestAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AAICharacter* AICharactere = Cast<AAICharacter>(InPawn);
    if (AICharactere && AICharactere->TreeAsset)
    {
        BlackboardComponent->InitializeBlackboard(*AICharactere->TreeAsset->BlackboardAsset);
        BehaviorTreeComponent->StartTree(*AICharactere->TreeAsset);

        
        AActor* PacmanActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPacMan::StaticClass());
        if (PacmanActor)
        {
            BlackboardComponent->SetValueAsObject(FName("TargetActor"), PacmanActor);
        }
    }
}

void ATestAIController::SetTargetActor(AActor* Target)
{
    if (BlackboardComponent && Target)
    {
        BlackboardComponent->SetValueAsObject(FName("TargetActor"), Target);
    }
}

