// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBaseCharacter.h"

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Jumping = false;
	CurrentWaypoint = 0;
	_JumpSpacing = 70.0f;
	_JumpMidTime = 0.5;

}

void AEnemyBaseCharacter::NavJumpTo(FVector Destination)
{
	if (CanJump()) {
		//perform all necessary one-time calculations for jump "physics".


		_JumpStartPosition = GetActorLocation();
		_JumpEndPosition = Destination;

		Jumping = true;
		FVector MovementDirection = (_JumpEndPosition - _JumpStartPosition).GetSafeNormal();

		//direction of jump
		float DirectionDot = FVector::DotProduct(MovementDirection, FVector::UpVector);

		//mid t position of jump highest point
		float _JumpMidTime = 0.5 + 0.5*DirectionDot;

		//base mid position of jump
		_JumpMidPosition = FMath::Lerp(_JumpStartPosition, _JumpEndPosition, _JumpMidTime);

		//add height to jump
		_JumpMidPosition.Z = FMath::Max(_JumpStartPosition.Z, _JumpEndPosition.Z) + _JumpSpacing;

		//position to be calculated and moved to
		FVector CurrentPosition;

		//distance
		float DistanceXY = FVector::DistSquaredXY(_JumpStartPosition, _JumpEndPosition);

		//distance to jump
		float JumpDistance = _JumpMidPosition.Z - _JumpStartPosition.Z;

		//distance to fall
		float FallDistance = _JumpMidPosition.Z - _JumpEndPosition.Z;

		//estimate total airtime for jump
		float Airtime = (JumpDistance + FallDistance) / 2.0f;

		//move speed for jump
		float MoveSpeed = 600;

		UCharacterMovementComponent * CMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (CMoveComp != nullptr) {
			MoveSpeed = CMoveComp->MaxWalkSpeed;
		}
		else {
			MoveSpeed = 600;
		}

		//duration of jump based on speed of traversal, yes this means that they'll fall faster if they're moving faster, but don't think about it.
		float _JumpDuration = (DistanceXY + Airtime) / MoveSpeed;

		//flattened forward direction of jump to angle character
		FVector FlatForward = FVector(MovementDirection.X, MovementDirection.Y, 0).GetSafeNormal();
		_JumpAngle = FlatForward.Rotation().Quaternion();


	}
}


// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*switch (MoveType) {
	case EMoveType::Complex:
		AEnemyBaseCharacter::ComplexUpdate(DeltaTime);
		break;
	case EMoveType::Simple:
		AEnemyBaseCharacter::SimpleUpdate(DeltaTime);
		break;
	case EMoveType::Stationary:

		break;
	}
	*/
	if (Jumping) {
		JumpTransition(DeltaTime);
	}

}

/*
void AEnemyBaseCharacter::ComplexUpdate(float DeltaTime)
{
	switch (_MoveState) {
		case EMoveState::Spawning:

		break;
	}
}

void AEnemyBaseCharacter::SimpleUpdate(float DeltaTime)
{

}

void AEnemyBaseCharacter::StationaryUpdate(float DeltaTime)
{

}*/

// Called to bind functionality to input
void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBaseCharacter::JumpTransition(float DeltaTime)
{
	//Z IS UP!

	UCharacterMovementComponent * CMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());

	_JumpTime += DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
	float JumpPercent = FMath::Clamp(1.0f / _JumpDuration * _JumpTime, 0.0f, 1.0f);
	FVector Midposition = FMath::Lerp(_JumpStartPosition, _JumpEndPosition, 0.5);
	Midposition.Z = FMath::Max(_JumpStartPosition.Z, _JumpEndPosition.Z) + _JumpSpacing;
	FVector CurrentPosition;
	float DistanceXY = FVector::DistSquaredXY(_JumpStartPosition, _JumpEndPosition);
	//float JumpDistance = Midposition.Z - _JumpStartPosition.Z;
	//float FallDistance = Midposition.Z - _JumpEndPosition.Z;
	//float Airtime = (JumpDistance + FallDistance) / 2.0f;
	//float MoveSpeed = 100;
	//if (CMoveComp!=nullptr) {
	//	MoveSpeed = CMoveComp->MaxWalkSpeed;
	//}
	//else {
	//	MoveSpeed = 600;
	//}
	if (JumpPercent >= 1.0f) {
		Jumping = false;
		CurrentPosition = _JumpEndPosition;
	}
	else {
		//CurrentPosition = blah
		FVector XY = FMath::LerpStable(_JumpStartPosition, _JumpEndPosition, JumpPercent);
		float Z = 0;
		if (_JumpTime < _JumpMidTime) {
			Z = FMath::InterpEaseIn(_JumpStartPosition.Z, _JumpMidPosition.Z, 1.0f / _JumpMidTime * _JumpTime, 2);
		}
		else if (_JumpTime > _JumpMidTime) {
			float timeleft = 1 - _JumpMidTime;
			float latertime = _JumpTime - _JumpMidTime;
			Z = FMath::InterpEaseOut(_JumpMidPosition.Z, _JumpEndPosition.Z, 1.0f / timeleft * latertime, 2);
		}
		else {
			Z = _JumpMidPosition.Z; //extremely unlikely, but still possible.
		}



		CurrentPosition = FVector(XY.X, XY.Y, Z);
	}

	SetActorLocationAndRotation(CurrentPosition, _JumpAngle, true, nullptr, ETeleportType::None);


}

