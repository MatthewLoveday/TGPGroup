// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameMovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlatformerGameMovingPlatform::APlatformerGameMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void APlatformerGameMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	EndLocation = MovementDirection + StartLocation;

	Difference = EndLocation - StartLocation;
}

// Called every frame
void APlatformerGameMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformerGameMovingPlatform::MovePlatformToEndLocation()
{
	if (!GetActorLocation().Equals(EndLocation))
	{
		FVector CurrentLocation = GetActorLocation();

		if (Difference.X != 0)
			CurrentLocation.X = GetActorLocation().X + MovementSpeed;

		if (Difference.Y != 0)
			CurrentLocation.Y = GetActorLocation().Y + MovementSpeed;

		if (Difference.Z != 0)
			CurrentLocation.Z = GetActorLocation().Z + MovementSpeed;

		SetActorLocation(CurrentLocation);
	}
}

void APlatformerGameMovingPlatform::MovePlatformToStartLocation()
{
	if (!GetActorLocation().Equals(StartLocation))
	{
		FVector MoveToLocation = GetActorLocation();

		if (Difference.X != 0)
			MoveToLocation.X = GetActorLocation().X - MovementSpeed;

		if (Difference.Y != 0)
			MoveToLocation.Y = GetActorLocation().Y - MovementSpeed;

		if (Difference.Z != 0)
			MoveToLocation.Z = GetActorLocation().Z - MovementSpeed;

		SetActorLocation(MoveToLocation);
	}
}
