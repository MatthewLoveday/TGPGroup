// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleporter.h"


// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::OnActorBeginOverlap(AActor* otherActor)
{
	BeginTeleport(otherActor);
}

void ATeleporter::BeginTeleport(AActor* otherActor)
{
	otherActor->TeleportTo(teleportLocation->GetActorUpVector(), teleportLocation->GetActorRotation());
}