#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FantomeRose.generated.h"

class AMyPacMan;

UCLASS()
class PACMAN_API AFantomeRose : public AActor
{
    GENERATED_BODY()

public:
    AFantomeRose();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY()
    AMyPacMan* PacMan;

    UPROPERTY(EditAnywhere)
    float Speed = 180.f;
};
