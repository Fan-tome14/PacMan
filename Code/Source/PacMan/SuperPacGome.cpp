// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperPacGome.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ASuperPacGome::OnEaten()
{
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->AddScore(100);
	}
	//PacMan->ActivateSuperMode();
}
