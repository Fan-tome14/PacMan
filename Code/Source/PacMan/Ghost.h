#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"
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

public:
    virtual void Tick(float DeltaTime) override;

    // --- Composants spécifiques ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent* CollisionBox;

    // --- Flipbooks spécifiques ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperFlipbook* BaseFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperFlipbook* DeadFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperFlipbook* FrightenFlipbook;

    // --- Flipbooks directionnels ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbooks|Directions")
    UPaperFlipbook* Flipbook_Up;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbooks|Directions")
    UPaperFlipbook* Flipbook_Down;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbooks|Directions")
    UPaperFlipbook* Flipbook_Left;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbooks|Directions")
    UPaperFlipbook* Flipbook_Right;


    // --- Behavior Tree ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UBehaviorTree* TreeAsset;

    // --- États ---
    bool IsDead;
    bool IsFrightened;
    bool IsNormal;
    bool bCanMove;

    // --- Position initiale pour reset ---
    FVector InitialLocation;
    FRotator InitialRotation;

    // --- Timer ---
    FTimerHandle FrightenedTimerHandle;

    // --- Fonctions ---
    void SetAliveMode();
    void SetDeadMode();
    void SetFrightenMode();
    void EndFrightenedMode();
    void Respawn();
    void UpdateFlipbookFromVelocity();
    void ResetGhost();

    // --- Collision ---
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);
};
