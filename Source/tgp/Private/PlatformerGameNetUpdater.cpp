// Fill out your copyright notice in the Description page of Project Settings.
#include "PlatformerGameNetUpdater.h"
#include "Components/BoxComponent.h"

APlatformerGameNetUpdater::APlatformerGameNetUpdater()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(70.0f, 70.0f, 10.0f));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APlatformerGameNetUpdater::HandleOverlap);
	CollisionComp->SetHiddenInGame(false);
	RootComponent = CollisionComp;
}

void APlatformerGameNetUpdater::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	SafetyNetRef->SetTeleportLocation(OtherActor->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Set Teleport Location"));
}