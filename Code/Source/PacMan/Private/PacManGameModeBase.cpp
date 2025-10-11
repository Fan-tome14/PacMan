#include "PacManGameModeBase.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "TimerManager.h"

void APacManGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // Forcer la g�n�ration de la NavMesh au d�but
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSys)
    {
        NavSys->Build();
        UE_LOG(LogTemp, Warning, TEXT("NavMesh rebuild demand� depuis GameMode !"));
    }
}
