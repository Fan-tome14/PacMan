// Fill out your copyright notice in the Description page of Project Settings.


#include "Mangeable.h"

#include "MyPacMan.h"
#include "PacGome.h"
#include "SuperPacGome.h"
#include "Components/BoxComponent.h"

// Sets default values
AMangeable::AMangeable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	staticMesh->SetupAttachment(RootComponent);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);

	// Bind overlap
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AMangeable::OnOverlap);

}

// Called when the game starts or when spawned
void AMangeable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMangeable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMangeable::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						   bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPacMan* PacMan = Cast<AMyPacMan>(OtherActor);
	if (PacMan)
	{
		// Si c’est une gomme normale
		if (APacGome* Gomme = Cast<APacGome>(this))
		{
			UE_LOG(LogTemp, Warning, TEXT("PacMan a mangé une Gomme normale !"));
			Gomme->OnEaten();
		}
		// Si c’est un Super Pack
		else if (ASuperPacGome* Super = Cast<ASuperPacGome>(this))
		{
			UE_LOG(LogTemp, Warning, TEXT("PacMan a mangé un Super Pack !"));
			Super->OnEaten();
		}
		Destroy();
	}
}

