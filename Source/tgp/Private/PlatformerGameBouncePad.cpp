// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameBouncePad.h"
#include "PlatformerGameCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlatformerGameBouncePad::APlatformerGameBouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &APlatformerGameBouncePad::HandleOverlap);
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlatformerGameBouncePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformerGameBouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformerGameBouncePad::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
											 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
											 bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *myCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (myCharacter)
		myCharacter->LaunchCharacter(LaunchAmount, false, false);
}