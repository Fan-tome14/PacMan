#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacEntity.generated.h"

UCLASS()
class PACMAN_API APacEntity : public APawn
{
	GENERATED_BODY()

public:
	APacEntity();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Mouvement
	void MoveForward(float Value);
	void MoveRight(float Value);
	bool PeutAller(const FVector& Direction);
	void ResetPosition();

	// Flipbook
	FVector InitialLocation;
	// Composants
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* PawnMovement;

	// Variables
	FVector DirectionCourante;
	FVector ProchaineDirection;
	float MoveSpeed;
};
