// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformerGameMovingPlatform.h"
#include "PlatformerGameOverlapPlatform.generated.h"

/**
 * 
 */
UCLASS()
class TGP_API APlatformerGameOverlapPlatform : public APlatformerGameMovingPlatform
{
	GENERATED_BODY()
	
protected:

	void BeginPlay();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent *CollisionComp;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
							UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
						  UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	bool bPlayerOnPlatform;
	
public:

	APlatformerGameOverlapPlatform();

	void Tick(float DeltaTime);
};
