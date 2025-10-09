#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Ghost.generated.h"

UCLASS()
class PACMAN_API AGhost : public APacEntity
{
	GENERATED_BODY()

public:
	AGhost();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle FrightenedTimerHandle;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ghost")
	float FrightenedDuration = 7.f; // exemple : 7 secondes
	
	// Flipbooks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprite")
	UPaperFlipbook* BaseFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprite")
	UPaperFlipbook* DeadFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprite")
	UPaperFlipbook* FrightenFlipbook;

	// États
	UPROPERTY(BlueprintReadWrite, Category="Etat")
	bool IsDead;

	UPROPERTY(BlueprintReadWrite, Category="Etat")
	bool IsFrightened;
	
	UPROPERTY(BlueprintReadWrite, Category="Etat")
	bool IsNormal;
	
	// Behavior Tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	UBehaviorTree* TreeAsset;

	// Méthodes d’état
	void SetAliveMode();
	void SetDeadMode();
	void SetFrightenMode();

	// Collision
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Flipbook orientation pour suivre la vitesse
	void UpdateFlipbookFromVelocity();
};
