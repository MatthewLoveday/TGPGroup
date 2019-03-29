// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBrokenChain.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "PlatformerGameCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


APickupBrokenChain::APickupBrokenChain()
{
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupBrokenChain::HandleOverlap);

	ConstantEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ConstantEffect"));
	ConstantEffect->bAutoActivate = true;
	ConstantEffect->SetupAttachment(RootComponent);

	BounceVal = 1;
}

void APickupBrokenChain::BeginPlay()
{
	Super::BeginPlay();

	if (IsCollected) HideCollectable();
	ConstantEffect->Deactivate();
}

void APickupBrokenChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollectableBounce(DeltaTime);
}

void APickupBrokenChain::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
									   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
									   bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyCharacter)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
		HideCollectable();
		IsCollected = true;
		ConstantEffect->Deactivate();
		CollectEffect->Activate();
	}

	UE_LOG(LogTemp, Log, TEXT("Overlap occured"));
}

void APickupBrokenChain::CollectableBounce(float DeltaTime)
{
	BounceVal++;

	double ZIncrease = sin(BounceVal * DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z += ZIncrease;

	SetActorLocation(CurrentLocation);
}