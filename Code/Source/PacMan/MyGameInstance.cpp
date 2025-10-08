#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

UMyGameInstance::UMyGameInstance()
{
	CurrentScore = 0;
	Lives = 3;
	TotalPieces = 86;     // 82 pac-gommes + 4 super pac-gommes
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
		// Si plus de vies → on charge GameOver
		UGameplayStatics::OpenLevel(GetWorld(), FName("GameOver"));
	}
}

void UMyGameInstance::ResetGame()
{
	CurrentScore = 0;
	Lives = 3;
	PiecesEaten = 0;
	UE_LOG(LogTemp, Log, TEXT("Nouvelle partie lancée !"));
}

void UMyGameInstance::OnPieceEaten()
{
	PiecesEaten++;

	UE_LOG(LogTemp, Log, TEXT("Pièce mangée (%d / %d)"), PiecesEaten, TotalPieces);

	if (PiecesEaten >= TotalPieces && TotalPieces > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TOUTES LES PIECES MANGEES ! Chargement de GameOver..."));
		UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/levels/GameOver"));
	}
}

