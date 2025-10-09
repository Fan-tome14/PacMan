#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/BoxComponent.h"
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

public:
	// Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionBox;

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

	UPROPERTY(BlueprintReadWrite, Category="Etat")
	bool bCanMove = true;

	// Behavior Tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	UBehaviorTree* TreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Respawn")
	float RespawnDelay = 5.f;

private:
	FTimerHandle FrightenedTimerHandle;

public:
	// Méthodes d’état
	void SetAliveMode();
	void SetDeadMode();
	void SetFrightenMode();
	void Respawn();

	// Collision
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	// Flipbook orientation
	void UpdateFlipbookFromVelocity();
};
