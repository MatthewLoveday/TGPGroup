// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameAutoMovingPlatform.h"
#include "Engine/Public/TimerManager.h"

void APlatformerGameAutoMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	bIsMovingToStartPos = false;
}

void APlatformerGameAutoMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPosition();

	if (bIsMovingToStartPos)
		MovePlatformToStartLocation();
	else
		MovePlatformToEndLocation();
}

void APlatformerGameAutoMovingPlatform::CheckPosition()
{
	if (EndLocation.Equals(GetActorLocation()))
		SetIsMoving();
	else if (StartLocation.Equals(GetActorLocation()))
		SetIsMoving();
}

void APlatformerGameAutoMovingPlatform::SetIsMoving()
{
	if (bIsMovingToStartPos)
		bIsMovingToStartPos = false;
	else
		bIsMovingToStartPos = true;
}