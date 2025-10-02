// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mangeable.h"
#include "PacGome.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacGome : public AMangeable
{
	GENERATED_BODY()

protected:
	virtual void OnEaten() override;
};
