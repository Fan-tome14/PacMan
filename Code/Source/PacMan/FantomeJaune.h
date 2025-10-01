#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FantomeJaune.generated.h"

class AMyPacMan;

UCLASS()
class PACMAN_API AFantomeJaune : public AActor
{
    GENERATED_BODY()

public:
    AFantomeJaune();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY()
    AMyPacMan* PacMan;

    UPROPERTY(EditAnywhere)
    float Speed = 300.f;

    FVector Direction;
};
