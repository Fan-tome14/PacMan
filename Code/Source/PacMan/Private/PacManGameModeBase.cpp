#include "PacManGameModeBase.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "TimerManager.h"

void APacManGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // Forcer la génération de la NavMesh au début
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSys)
    {
        NavSys->Build();
        UE_LOG(LogTemp, Warning, TEXT("NavMesh rebuild demandé depuis GameMode !"));
    }
}
