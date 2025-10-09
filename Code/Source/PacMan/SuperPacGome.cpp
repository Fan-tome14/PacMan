#include "SuperPacGome.h"
#include "Ghost.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" // Pour TActorIterator

void ASuperPacGome::OnEaten()
{
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->AddScore(100);
		GI->OnPieceEaten();
	}

	// Parcourt tous les ghosts dans le monde et les rend effrayés
	for (TActorIterator<AGhost> It(GetWorld()); It; ++It)
	{
		AGhost* Ghost = *It;
		if (Ghost)
		{
			UE_LOG(LogTemp, Warning, TEXT("j'ai peur"));
			Ghost->SetFrightenMode();
		}
	}

	// PacMan->ActivateSuperMode(); // si tu veux activer le mode super sur Pac-Man
}
