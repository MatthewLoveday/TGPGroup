// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameOverlapPlatform.h"
#include "PlatformerGameCharacter.h"
#include "Components/BoxComponent.h"

APlatformerGameOverlapPlatform::APlatformerGameOverlapPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APlatformerGameOverlapPlatform::HandleBeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &APlatformerGameOverlapPlatform::HandleEndOverlap);
	CollisionComp->SetupAttachment(RootComponent);

	bPlayerOnPlatform = false;
}

void APlatformerGameOverlapPlatform::BeginPlay()
{
	Super::BeginPlay();
}


void APlatformerGameOverlapPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerOnPlatform)
		MovePlatformToEndLocation();
	else
		MovePlatformToStartLocation();

}

void APlatformerGameOverlapPlatform::HandleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyCharacter)
		bPlayerOnPlatform = true;
}

void APlatformerGameOverlapPlatform::HandleEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	bPlayerOnPlatform = false;
}


