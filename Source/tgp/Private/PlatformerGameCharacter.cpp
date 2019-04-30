// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlatformerGameCharacter::APlatformerGameCharacter()
{
	alive = true;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetupAttachment(CameraBoom);
}

void APlatformerGameCharacter::ChangeMoveset(EMovesetEnum newMoveSet)
{
	if(moveSet == newMoveSet)
	{
		return;
	}

	
	switch(moveSet) //Exit Conditions
	{
	case EMovesetEnum::M_Default:
		ExitDefaultMoveSet();
		break;

	case EMovesetEnum::M_Balloon:
		ExitBalloonMoveSet();
		break;

	case EMovesetEnum::M_Helicopter:
		ExitHeliMoveSet();
		break;

	default:
		break;
	}

	moveSet = newMoveSet;

	switch(newMoveSet) //Entry Conditions
	{
	case EMovesetEnum::M_Default:
		EnterDefaultMoveSet();
		break;

	case EMovesetEnum::M_Balloon:
		EnterBalloonMoveSet();
		break;

	case EMovesetEnum::M_Helicopter:
		EnterHeliMoveSet();
		break;

	default:
		break;
	}
}

bool APlatformerGameCharacter::IsAlive() const
{
	return alive;
}

void APlatformerGameCharacter::Respawn_Implementation()
{
	alive = true;
}

EMovesetEnum APlatformerGameCharacter::GetMoveset() const
{
	return moveSet;
}

// Called when the game starts or when spawned
void APlatformerGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformerGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlatformerGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
}

FHitResult APlatformerGameCharacter::PerformWallTrace(ECollisionChannel traceChannel, float ZOffset, float length, bool DrawTrace, bool invert)
{
	FHitResult result;

	FCollisionQueryParams queryParams;
	FString tTag = "PWallTag" + FString::SanitizeFloat(ZOffset);

	if(DrawTrace)
	{
		queryParams.TraceTag = *tTag;
	}
	if(GetWorld())
	{
		GetWorld()->LineTraceSingleByChannel(result, 
			GetActorLocation() + FVector(0.0f, 0.0f, ZOffset),
			(GetActorLocation() + FVector(0.0f, 0.0f, ZOffset) + ((invert ? -1 : 1) * GetActorForwardVector()) * length), 
			traceChannel, 
			queryParams);
		
		if(DrawTrace)
		{
			GetWorld()->DebugDrawTraceTag = queryParams.TraceTag;			
		}
	}

	return result;
}

FHitResult APlatformerGameCharacter::PerformCircleTrace(ECollisionChannel traceChannel, float ZOffset, float radius, bool DrawDebug)
{
	FHitResult result;

	FCollisionQueryParams queryParams;
	FString tTag = "PCircleTrace" + FString::SanitizeFloat(ZOffset);

	if(DrawDebug)
	{
		queryParams.TraceTag = *tTag;
	}

	if(GetWorld())
	{
		GetWorld()->SweepSingleByChannel(result, 
			GetActorLocation() + FVector(0.0f, 0.0f, ZOffset),
			GetActorLocation() + FVector(0.0f, 0.0f, ZOffset),
			FQuat::Identity,
			traceChannel,
			FCollisionShape::MakeBox(FVector(radius, radius, 1.0)),
			queryParams
		);

		if(DrawDebug)
		{
			GetWorld()->DebugDrawTraceTag = queryParams.TraceTag;
		}
	}

	return result;
}

