#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FantomeRouge.generated.h"

class AMyPacMan;

UCLASS()
class PACMAN_API AFantomeRouge : public AActor
{
    GENERATED_BODY()

public:
    AFantomeRouge();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY()
    AMyPacMan* PacMan;

    UPROPERTY(EditAnywhere)
    float Speed = 200.f;
};
