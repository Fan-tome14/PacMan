#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FantomeBleu.generated.h"

class AMyPacMan;

UCLASS()
class PACMAN_API AFantomeBleu : public AActor
{
    GENERATED_BODY()

public:
    AFantomeBleu();

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
