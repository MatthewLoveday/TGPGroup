// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"
#include "PlatformerGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = SphereCollision;
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::HandleOverlap);
	SphereCollision->SetHiddenInGame(false);

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, 
							   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, 
							   bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyCharacter)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
	}

	UE_LOG(LogTemp, Log, TEXT("Overlap occured"));
}