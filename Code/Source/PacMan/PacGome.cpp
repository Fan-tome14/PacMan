// Fill out your copyright notice in the Description page of Project Settings.


#include "PacGome.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void APacGome::OnEaten()
{
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->AddScore(10);

		GI->OnPieceEaten();
	}
}
