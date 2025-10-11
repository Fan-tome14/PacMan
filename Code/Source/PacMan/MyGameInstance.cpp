// MyGameInstance.cpp
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Ghost.h"
#include "MyPacMan.h"

UMyGameInstance::UMyGameInstance()
{
    CurrentScore = 0;
    Lives = 3;
    TotalPieces = 86;
    PiecesEaten = 0;
    bIsWinner = false;
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

    // Réinitialisation de Pac-Man
    AMyPacMan* Pac = Cast<AMyPacMan>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Pac)
    {
        Pac->Die(); // animation de mort + repositionnement géré par Pac-Man
    }

    // Réinitialisation des fantômes
    TArray<AActor*> FoundGhosts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGhost::StaticClass(), FoundGhosts);
    for (AActor* Actor : FoundGhosts)
    {
        AGhost* Ghost = Cast<AGhost>(Actor);
        if (Ghost)
        {
            Ghost->ResetGhost();
            Ghost->SetAliveMode();
        }
    }

    // Si plus de vie → déclenchement GameOver (dans Blueprint)
    if (Lives <= 0)
    {
        bIsWinner = false;
        UE_LOG(LogTemp, Warning, TEXT("Toutes les vies perdues — appel de OnGameOver()"));
        OnGameOver(); //  Appelé dans Blueprint
    }
}

void UMyGameInstance::ResetGame()
{
    CurrentScore = 0;
    Lives = 3;
    PiecesEaten = 0;
    TotalPieces = 86;
    bIsWinner = false;

    UE_LOG(LogTemp, Log, TEXT("Nouvelle partie lancée ! Variables réinitialisées !"));

    // Reset des fantômes
    TArray<AActor*> FoundGhosts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGhost::StaticClass(), FoundGhosts);
    for (AActor* Actor : FoundGhosts)
    {
        AGhost* Ghost = Cast<AGhost>(Actor);
        if (Ghost)
        {
            Ghost->ResetGhost();
            Ghost->SetAliveMode();
        }
    }

    // Reset de Pac-Man
    AMyPacMan* Pac = Cast<AMyPacMan>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Pac)
    {
        Pac->ResetPosition();
    }
}

void UMyGameInstance::OnPieceEaten()
{
    PiecesEaten++;

    UE_LOG(LogTemp, Log, TEXT("Pièce mangée (%d / %d)"), PiecesEaten, TotalPieces);

    // Si toutes les pièces sont mangées → victoire → appel Blueprint
    if (PiecesEaten >= TotalPieces)
    {
        bIsWinner = true;
        UE_LOG(LogTemp, Warning, TEXT("Toutes les pièces mangées — appel de OnGameOver()"));
        OnGameOver(); //  Appelé dans Blueprint
    }
}
