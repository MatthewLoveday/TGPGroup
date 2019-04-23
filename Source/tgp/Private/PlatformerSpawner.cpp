// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerSpawner.h"
#include "Engine/World.h"

// Sets default values
APlatformerSpawner::APlatformerSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformerSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* APlatformerSpawner::SpawnActor(TSubclassOf<AActor> BPToSpawn)
{
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(BPToSpawn, GetActorTransform());
	return spawnedActor;
}
