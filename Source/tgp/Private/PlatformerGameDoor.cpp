// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameDoor.h"


// Sets default values
APlatformerGameDoor::APlatformerGameDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlatformerGameDoor::BeginPlay()
{
	Super::BeginPlay();
	
	StartRotation = GetActorRotation();
}

// Called every frame
void APlatformerGameDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformerGameDoor::MoveToSetRotation()
{

}

void APlatformerGameDoor::MoveToStartRotation()
{

}