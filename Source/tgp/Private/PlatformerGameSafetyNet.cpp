// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameSafetyNet.h"
#include "Components/BoxComponent.h"
#include "PlatformerGameCharacter.h"

// Sets default values
APlatformerGameSafetyNet::APlatformerGameSafetyNet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(70.0f, 70.0f, 10.0f));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APlatformerGameSafetyNet::HandleOverlap);
	CollisionComp->SetHiddenInGame(false);
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void APlatformerGameSafetyNet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformerGameSafetyNet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformerGameSafetyNet::SetTeleportLocation(const FVector & newLocation)
{
	TeleportLocation = newLocation;
}

void APlatformerGameSafetyNet::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
											 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
											 bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyChar = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyChar)
		MyChar->SetActorLocation(TeleportLocation);
}