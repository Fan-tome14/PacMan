#include "MyGameInstance.h"

#include "Ghost.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

UMyGameInstance::UMyGameInstance()
{
	CurrentScore = 0;
	Lives = 3;
	TotalPieces = 86;
	PiecesEaten = 0;
}



void UMyGameInstance::AddScore(int32 Amount)
{
	CurrentScore += Amount;
	UE_LOG(LogTemp, Log, TEXT("Nouveau Score: %d"), CurrentScore);
}

void UMyGameInstance::LoseLife()
{
	if (Lives > 0)
		Lives--;

	UE_LOG(LogTemp, Warning, TEXT("Vies restantes: %d"), Lives);

	if (Lives <= 0)
	{
		bIsWinner = false;
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/levels/GameOver"));
	}
}

void UMyGameInstance::ResetGame()
{
	CurrentScore = 0;
	Lives = 3;
	PiecesEaten = 0;
	TotalPieces = 86;

	UE_LOG(LogTemp, Log, TEXT("Nouvelle partie lancée ! Variables réinitialisées !"));

	// Réinitialise tous les fantômes
	TArray<AActor*> FoundGhosts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGhost::StaticClass(), FoundGhosts);

	for (AActor* Actor : FoundGhosts)
	{
		AGhost* Ghost = Cast<AGhost>(Actor);
		if (Ghost)
		{
			Ghost->ResetGhost();
		}
	}
}

void UMyGameInstance::OnPieceEaten()
{
	PiecesEaten++;

	UE_LOG(LogTemp, Log, TEXT("Pièce mangée (%d / %d)"), PiecesEaten, TotalPieces);

	if (PiecesEaten >= TotalPieces)
	{
		bIsWinner = true;
		UE_LOG(LogTemp, Warning, TEXT("TOUTES LES PIECES MANGEES ! Chargement de GameOver..."));
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/levels/GameOver"));
	}
}
