// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorTrigger::ADoorTrigger()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
}

// Called when the game starts or when spawned
void ADoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

