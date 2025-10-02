// Fill out your copyright notice in the Description page of Project Settings.

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

	// Score actuel du joueur
	UPROPERTY(BlueprintReadWrite, Category="Game Data")
	int32 CurrentScore;

	// Nombre de vies restantes
	UPROPERTY(BlueprintReadWrite, Category="Game Data")
	int32 Lives;

	// --- Fonctions utilitaires ---

	// Ajoute du score
	UFUNCTION(BlueprintCallable, Category="Game Data")
	void AddScore(int32 Amount);

	// Enlève une vie
	UFUNCTION(BlueprintCallable, Category="Game Data")
	void LoseLife();

	// Reset des données (nouvelle partie)
	UFUNCTION(BlueprintCallable, Category="Game Data")
	void ResetGame();
};
