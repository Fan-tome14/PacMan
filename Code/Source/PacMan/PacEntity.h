#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
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
	virtual void Tick(float DeltaTime) override;

	// --- Composants ---

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* PawnMovement;

	// --- Variables de mouvement ---
	FVector DirectionCourante;
	FVector ProchaineDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mouvement")
	float MoveSpeed;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	bool PeutAller(const FVector& Direction);

	void UpdateFlipbookOrientation();
};
