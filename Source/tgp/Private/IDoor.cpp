// Fill out your copyright notice in the Description page of Project Settings.

#include "IDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AIDoor::AIDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MoveToStartLocation = false;
	MoveToStartRotation = false;

	CanOpen   = false;
	CanRotate = false;
}

// Called when the game starts or when spawned
void AIDoor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();

	EndLocation = DistanceToMove + StartLocation;
	EndRotation = DistanceToRotate + StartRotation;

	DistanceToEndLoc = EndLocation - StartLocation;
	DistanceToEndRot = EndRotation - StartRotation;
}

// Called every frame
void AIDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanOpen)
		SlideDoorOpen();
	
	if (MoveToStartLocation)
		SlideDoorClose();

	if (CanRotate)
		RotateDoorOpen();

	if (MoveToStartRotation)
		RotateDoorClose();
}

void AIDoor::SlideDoorOpen()
{
	if (GetActorLocation().Equals(EndLocation))
	{
		CanOpen = false;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();

		if (DistanceToEndLoc.X != 0.0f)
			CurrentLocation.X += 1.0f;

		if (DistanceToEndLoc.Y != 0.0f)
			CurrentLocation.Y += 1.0f;

		if (DistanceToEndLoc.Z != 0.0f)
			CurrentLocation.Z += 1.0f;

		SetActorLocation(CurrentLocation);
	}
}

void AIDoor::SlideDoorClose()
{
	if (GetActorLocation().Equals(StartLocation))
	{
		MoveToStartLocation = false;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();

		if (DistanceToEndLoc.X != 0.0f)
			CurrentLocation.X -= 1.0f;

		if (DistanceToEndLoc.Y != 0.0f)
			CurrentLocation.Y -= 1.0f;

		if (DistanceToEndLoc.Z != 0.0f)
			CurrentLocation.Z -= 1.0f;

		SetActorLocation(CurrentLocation);
	}
}

void AIDoor::RotateDoorOpen()
{
	if (GetActorRotation().Vector().Equals(EndRotation.Vector()))
	{
		CanRotate = false;
	}
	else
	{
		FRotator CurrentRotation = GetActorRotation();

		if (DistanceToEndRot.Roll != 0.0f)
			CurrentRotation.Roll += 1.0f;

		if (DistanceToEndRot.Pitch != 0.0f)
			CurrentRotation.Pitch += 1.0f;

		if (DistanceToEndRot.Yaw != 0.0f)
			CurrentRotation.Yaw += 1.0f;

		SetActorRotation(CurrentRotation);
	}
}

void AIDoor::RotateDoorClose()
{
	if (GetActorRotation().Vector().Equals(StartRotation.Vector()))
	{
		MoveToStartRotation = false;
	}
	else
	{
		FRotator CurrentRotation = GetActorRotation();

		if (DistanceToEndRot.Roll != 0.0f)
			CurrentRotation.Roll -= 1.0f;

		if (DistanceToEndRot.Pitch != 0.0f)
			CurrentRotation.Pitch -= 1.0f;

		if (DistanceToEndRot.Yaw != 0.0f)
			CurrentRotation.Yaw -= 1.0f;

		SetActorRotation(CurrentRotation);
	}
}