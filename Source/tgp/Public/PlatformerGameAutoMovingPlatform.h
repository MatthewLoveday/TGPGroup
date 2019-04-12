// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformerGameMovingPlatform.h"
#include "PlatformerGameAutoMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class TGP_API APlatformerGameAutoMovingPlatform : public APlatformerGameMovingPlatform
{
	GENERATED_BODY()
	
protected:

	void BeginPlay();

	void CheckPosition();

	void SetIsMoving();

	UPROPERTY(EditDefaultsOnly, Category = "WaitTime")
	float StationaryTime;

	bool bIsMovingToStartPos;

	FTimerHandle Timer;

public:
	
	void Tick(float DeltaTime);

};
