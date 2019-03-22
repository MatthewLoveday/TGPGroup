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
}

void APickupBrokenChain::BeginPlay()
{
	Super::BeginPlay();
}

void APickupBrokenChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ConstantEffect->IsActive() && CollectEffect->HasCompleted())
	{
		UE_LOG(LogTemp, Log, TEXT("Particle Finished"));
		Destroy();
	}
}

void APickupBrokenChain::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
									   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
									   bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyCharacter)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereCollision->SetVisibility(false);
		MeshComp->SetVisibility(false);
		ConstantEffect->Deactivate();
		CollectEffect->Activate();
	}

	UE_LOG(LogTemp, Log, TEXT("Overlap occured"));
}