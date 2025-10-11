// MyGameInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * GameInstance principal pour Pac-Man
 * Gère le score, les vies, les pièces mangées et l’état de victoire/défaite.
 * Le changement de scène (GameOver) se fait désormais dans le Blueprint via OnGameOver().
 */
UCLASS()
class PACMAN_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Constructeur
	UMyGameInstance();

	/** Score actuel du joueur */
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 CurrentScore;

	/** Nombre de vies restantes */
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 Lives;

	/** Nombre total de pac-gommes (classiques + super) */
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 TotalPieces;

	/** Nombre de pac-gommes mangées */
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 PiecesEaten;

	/** Indique si le joueur a gagné */
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	bool bIsWinner;

	/** Appelée lorsqu’une pac-gomme est mangée */
	void OnPieceEaten();

	/** Ajoute un score */
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void AddScore(int32 Amount);

	/** Retire une vie */
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void LoseLife();

	/** Réinitialise toutes les variables et repositionne Pac-Man + fantômes */
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void ResetGame();

	/**  Événement implémenté dans Blueprint : gère la fin de partie */
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Flow")
	void OnGameOver();
};
