#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionPacMan;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ComposantMesh;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* ComposantMouvement;

	void MoveForward(float Value);
	void MoveRight(float Value);

	bool PeutAller(FVector Direction);

	UFUNCTION()
	void OnOverlapPiece(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector DirectionCourante = FVector::ZeroVector;
};
