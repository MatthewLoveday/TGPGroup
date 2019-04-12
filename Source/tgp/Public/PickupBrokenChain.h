// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "PickupBrokenChain.generated.h"

class UParticleSystemComponent;

UCLASS()
class TGP_API APickupBrokenChain : public APickupBase
{
	GENERATED_BODY()
	
public:
	APickupBrokenChain();

	virtual void Tick(float DeltaTime);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystemComponent *ConstantEffect;

	int BounceVal;

	virtual void BeginPlay();

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
					   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
					   bool bFromSweep, const FHitResult &SweepResult);
	
	void CollectableBounce(float DeltaTime);

};
