// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "PickupCollectable.generated.h"

class UParticleSystemComponent;

UCLASS()
class TGP_API APickupCollectable : public APickupBase
{
	GENERATED_BODY()
	
public:
	APickupCollectable();

protected:
	
	virtual void BeginPlay();

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
					   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
					   bool bFromSweep, const FHitResult &SweepResult);

};
