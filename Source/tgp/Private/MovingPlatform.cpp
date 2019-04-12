// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	startPos = GetActorLocation();
}

float f = 0;

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("f: %f, index: %i"), f, currIndex));

	Super::Tick(DeltaTime);
	if (waypoints.Num() > 0) {
		f += (DeltaTime) * movementSpeed;
		if (f >= 1.0f) {
			f = 0.0f;
			startPos = GetActorLocation();
			if (dirModifier == 1) {
				if (currIndex == waypoints.Num() - 1) {
					dirModifier *= -1;
					currIndex--;
				}
				else
					currIndex++;
			} else {
				if (currIndex == 0) {
					dirModifier *= -1;
					currIndex++;
				}
				else
					currIndex--;
			}
		}
		SetActorLocation(FMath::Lerp(startPos, waypoints[currIndex], f));

	}

}

