// Fill out your copyright notice in the Description page of Project Settings.

#include "IDoor.h"
#include "Components/StaticMeshComponent.h"

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
			CurrentLocation.X += MovementSpeed;

		if (DistanceToEndLoc.Y != 0.0f)
			CurrentLocation.Y += MovementSpeed;

		if (DistanceToEndLoc.Z != 0.0f)
			CurrentLocation.Z += MovementSpeed;

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
			CurrentLocation.X -= MovementSpeed;

		if (DistanceToEndLoc.Y != 0.0f)
			CurrentLocation.Y -= MovementSpeed;

		if (DistanceToEndLoc.Z != 0.0f)
			CurrentLocation.Z -= MovementSpeed;

		SetActorLocation(CurrentLocation);
	}
}

void AIDoor::RotateDoorOpen()
{
	/*
	* Converting the rotator to a vector and then using the equals function
	* becuase the rotator equals function doesn't work at the moment and may be bugged
	*/
	if (GetActorRotation().Vector().Equals(EndRotation.Vector()))
	{
		CanRotate = false;
	}
	else
	{
		FRotator CurrentRotation = GetActorRotation();

		if (DistanceToEndRot.Roll != 0.0f)
			CurrentRotation.Roll += RotationSpeed;

		if (DistanceToEndRot.Pitch != 0.0f)
			CurrentRotation.Pitch += RotationSpeed;

		if (DistanceToEndRot.Yaw != 0.0f)
			CurrentRotation.Yaw += RotationSpeed;

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
			CurrentRotation.Roll -= RotationSpeed;

		if (DistanceToEndRot.Pitch != 0.0f)
			CurrentRotation.Pitch -= RotationSpeed;

		if (DistanceToEndRot.Yaw != 0.0f)
			CurrentRotation.Yaw -= RotationSpeed;

		SetActorRotation(CurrentRotation);
	}
}