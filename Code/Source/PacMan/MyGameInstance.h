#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class PACMAN_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 CurrentScore;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 Lives;

	// Nombre total de pac-gommes (classiques + super)
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 TotalPieces;

	// Nombre de pac-gommes mangées
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	int32 PiecesEaten;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void LoseLife();

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void ResetGame();

	// Appelée à chaque fois qu'une pac-gomme est mangée
	void OnPieceEaten();
};
