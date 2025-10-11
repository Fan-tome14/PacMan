#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPacMan.generated.h"

UCLASS()
class PACMAN_API AMyPacMan : public APawn
{
	GENERATED_BODY()

public:
	AMyPacMan();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	bool PeutAller(FVector Direction);

	void UpdateFlipbookRotation();

	/** Gérer la mort et le reset */
	void Die();
	void ResetPosition();

private:
	FVector DirectionCourante = FVector::ZeroVector;
	FVector InitialLocation;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionPacMan;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* DeadFlipbook;

	UPaperFlipbook* BaseFlipbook;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* ComposantMouvement;

	/** Timer handle pour reset après le flipbook mort */
	FTimerHandle DeathTimerHandle;
};
