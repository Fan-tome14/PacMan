// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetAliveMode.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API UBTTask_SetAliveMode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetAliveMode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
