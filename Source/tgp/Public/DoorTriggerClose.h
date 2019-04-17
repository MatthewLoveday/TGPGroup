// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorTrigger.h"
#include "DoorTriggerClose.generated.h"

/**
 * 
 */
UCLASS()
class TGP_API ADoorTriggerClose : public ADoorTrigger
{
	GENERATED_BODY()
	
	
	ADoorTriggerClose();

	UFUNCTION()
		void HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	
};
