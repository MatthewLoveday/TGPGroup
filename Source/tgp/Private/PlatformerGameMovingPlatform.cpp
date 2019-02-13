// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameMovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlatformerGameCharacter.h"

// Sets default values
APlatformerGameMovingPlatform::APlatformerGameMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APlatformerGameMovingPlatform::HandleBeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &APlatformerGameMovingPlatform::HandleEndOverlap);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	bPlayerOnPlatform = false;
}

// Called when the game starts or when spawned
void APlatformerGameMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	

	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("StartLocation - %f:%f:%f"), StartLocation.X, StartLocation.Y, StartLocation.Z);

	EndLocation = MovementDirection + StartLocation;
	UE_LOG(LogTemp, Log, TEXT("EndLocation - %f:%f:%f"), EndLocation.X, EndLocation.Y, EndLocation.Z);

	Difference = EndLocation - StartLocation;
	UE_LOG(LogTemp, Log, TEXT("Difference - %f:%f:%f"), Difference.X, Difference.Y, Difference.Z );
}

// Called every frame
void APlatformerGameMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerOnPlatform)
		MovePlatformToEndLocation();
	else
		MovePlatformToStartLocation();
}

void APlatformerGameMovingPlatform::HandleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
														UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
														bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *MyCharacter = Cast<APlatformerGameCharacter>(OtherActor);

	if (MyCharacter)
		bPlayerOnPlatform = true;
}

void APlatformerGameMovingPlatform::HandleEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
													 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	bPlayerOnPlatform = false;
}

void APlatformerGameMovingPlatform::MovePlatformToEndLocation()
{
	if (!GetActorLocation().Equals(EndLocation))
	{
		FVector CurrentLocation = GetActorLocation();

		if (Difference.X != 0)
			CurrentLocation.X = GetActorLocation().X + MovementSpeed;

		if (Difference.Y != 0)
			CurrentLocation.Y = GetActorLocation().Y + MovementSpeed;

		if (Difference.Z != 0)
			CurrentLocation.Z = GetActorLocation().Z + MovementSpeed;

		SetActorLocation(CurrentLocation);
	}
}

void APlatformerGameMovingPlatform::MovePlatformToStartLocation()
{
	if (!GetActorLocation().Equals(StartLocation))
	{
		FVector MoveToLocation = GetActorLocation();

		if (Difference.X != 0)
			MoveToLocation.X = GetActorLocation().X - MovementSpeed;

		if (Difference.Y != 0)
			MoveToLocation.Y = GetActorLocation().Y - MovementSpeed;

		if (Difference.Z != 0)
			MoveToLocation.Z = GetActorLocation().Z - MovementSpeed;

		SetActorLocation(MoveToLocation);
	}
}