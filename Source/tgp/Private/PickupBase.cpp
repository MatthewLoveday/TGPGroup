// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereCollision;
	
	SphereCollision->SetHiddenInGame(false);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetGenerateOverlapEvents(false);
	MeshComp->SetupAttachment(RootComponent);

	CollectEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("CollectEffect"));
	CollectEffect->bAutoActivate = false;
	CollectEffect->SetupAttachment(RootComponent);

	RotationSpeed = 1;
	CurrentRotation = GetActorRotation();
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateActor();
}

void APickupBase::RotateActor()
{
	CurrentRotation.Yaw += RotationSpeed;
	SetActorRotation(CurrentRotation);
}