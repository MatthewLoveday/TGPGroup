// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "tgp.h"
#include "CoreMinimal.h"
#include "PlatformerGameSafetyNet.h"
#include "PlatformerGameNetUpdater.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TGP_API APlatformerGameNetUpdater : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent *CollisionComp;

	APlatformerGameNetUpdater();

	void HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, Category = "Teleport Options")
		FVector NewTeleportLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =TeleportReference)
	APlatformerGameSafetyNet* SafetyNetRef;

};
