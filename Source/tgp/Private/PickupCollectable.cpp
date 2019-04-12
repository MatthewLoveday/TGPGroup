// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupCollectable.h"
#include "Components/SphereComponent.h"
#include "PlatformerGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

APickupCollectable::APickupCollectable()
{
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupCollectable::HandleOverlap);
}

void APickupCollectable::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
									   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
									   bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyCharacter)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
		HideCollectable();
		IsCollected = true;
		MyCharacter->IncrementCollectableCount();
		CollectEffect->Activate();
	}
}
