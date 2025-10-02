// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mangeable.h"
#include "SuperPacGome.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API ASuperPacGome : public AMangeable
{
	GENERATED_BODY()
protected:
	virtual void OnEaten() override;
};
