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

private:
	FVector DirectionCourante = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionPacMan;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* ComposantMouvement;
};
