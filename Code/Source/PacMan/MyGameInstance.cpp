#include "MyGameInstance.h"
#include "Engine/Engine.h"

UMyGameInstance::UMyGameInstance()
{
	// Valeurs par défaut
	CurrentScore = 0;
	Lives = 3;
}

void UMyGameInstance::AddScore(int32 Amount)
{
	CurrentScore += Amount;

	UE_LOG(LogTemp, Log, TEXT("Nouveau Score: %d"), CurrentScore);
}

void UMyGameInstance::LoseLife()
{
	if (Lives > 0)
	{
		Lives--;
	}

	UE_LOG(LogTemp, Warning, TEXT("Vies restantes: %d"), Lives);

	if (Lives <= 0)
	{
		//ici je vais faire loadlevel mais pas créer
	}
}

void UMyGameInstance::ResetGame()
{
	CurrentScore = 0;
	Lives = 3;
	UE_LOG(LogTemp, Log, TEXT("Nouvelle partie lancée !"));
}
