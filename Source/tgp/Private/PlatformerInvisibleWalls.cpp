// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerInvisibleWalls.h"
#include "Components/BoxComponent.h"

#define ECC_WallJumpable ECC_GameTraceChannel1

// Sets default values
APlatformerInvisibleWalls::APlatformerInvisibleWalls()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(70.0f, 70.0f, 10.0f));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_WallJumpable, ECR_Ignore);
	CollisionComp->SetHiddenInGame(false);
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void APlatformerInvisibleWalls::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformerInvisibleWalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

