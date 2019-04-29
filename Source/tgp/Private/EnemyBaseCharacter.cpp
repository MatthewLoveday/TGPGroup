// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBaseCharacter.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule != nullptr) {
		_PlayerHeight = Capsule->GetScaledCapsuleHalfHeight();
	}
	else {
		_PlayerHeight = 40.0f;
	}
}

void AEnemyBaseCharacter::NavJumpTo(FVector Destination)
{
	if (CanJump() && (MoveType == EMoveType::Simple || MoveType == EMoveType::Complex)) {
		//perform all necessary one-time calculations for jump "physics".


		_JumpStartPosition = GetActorLocation()-FVector(0,0,_PlayerHeight);
		_JumpEndPosition = Destination;
		_JumpTime = 0;

		Jumping = true;
		FVector MovementDirection = (_JumpEndPosition - _JumpStartPosition).GetSafeNormal();

		//direction of jump
		float DirectionDot = FVector::DotProduct(MovementDirection, FVector::UpVector);

		//mid t position of jump highest point
		_JumpMidTime = 0.5 + 0.5*DirectionDot;

		//base mid position of jump
		_JumpMidPosition = FMath::Lerp(_JumpStartPosition, _JumpEndPosition, _JumpMidTime);

		//add height to jump
		_JumpMidPosition.Z = FMath::Max(_JumpStartPosition.Z, _JumpEndPosition.Z) + _JumpSpacing;

		//position to be calculated and moved to
		FVector CurrentPosition;

		//distance
		float DistanceXY = FVector::DistXY(_JumpStartPosition, _JumpEndPosition);

		//distance to jump
		float JumpDistance = _JumpMidPosition.Z - _JumpStartPosition.Z;

		//distance to fall
		float FallDistance = _JumpMidPosition.Z - _JumpEndPosition.Z;

		//estimate total airtime for jump
		float Airtime = (JumpDistance + FallDistance) / 2.0f;

		//move speed for jump
		float MoveSpeed = 500;

		UCharacterMovementComponent * CMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		/*if (CMoveComp != nullptr) {
			MoveSpeed = CMoveComp->MaxWalkSpeed;
		}
		else {
			MoveSpeed = 300;
		}*/

		//duration of jump based on speed of traversal, yes this means that they'll fall faster if they're moving faster, but don't think about it.
		_JumpDuration = (DistanceXY + Airtime) / MoveSpeed;
		_JumpPercent = 0;
		//flattened forward direction of jump to angle character
		FVector FlatForward = FVector(MovementDirection.X, MovementDirection.Y, 0).GetSafeNormal();
		_JumpAngle = FlatForward.Rotation().Quaternion();

		//DrawDebugLine(GetWorld(), _JumpStartPosition, _JumpMidPosition, FColor(255, 0, 0), true, 10.0f, 0, 10.0f);
		//DrawDebugLine(GetWorld(), _JumpMidPosition, _JumpEndPosition, FColor(255, 0, 0), true, 10.0f, 0, 10.0f);

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
	Lifetime += DeltaTime;
	if (Jumping) {
		JumpTransition(DeltaTime);
	}

}

/*

void AEnemyBaseCharacter::StationaryUpdate(float DeltaTime)
{

}

void AEnemyBaseCharacter::SimpleUpdate(float DeltaTime)
{

}

void AEnemyBaseCharacter::ComplexUpdate(float DeltaTime)
{
	switch (_MoveState) {
		case EMoveState::Spawning:

		break;
	}
}

*/

// Called to bind functionality to input
void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBaseCharacter::JumpTransition(float DeltaTime)
{
	//Z IS UP!

	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
	UCharacterMovementComponent * CMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());

	_JumpTime += DeltaTime;
	FVector PreviousPosition = GetActorLocation();

	_JumpPercent = FMath::Clamp(1.0f / _JumpDuration * _JumpTime, 0.0f, 1.0f);

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
	if (_JumpPercent >= 1.0f) {
		Jumping = false;
		CurrentPosition = _JumpEndPosition + FVector(0, 0, 20);
	}
	else {
		//CurrentPosition = blah
		FVector XY = FMath::LerpStable(_JumpStartPosition, _JumpEndPosition, _JumpPercent);
		float Z = 0.0f;
		if (_JumpPercent < _JumpMidTime) {
			Z = FMath::InterpEaseOut(_JumpStartPosition.Z, _JumpMidPosition.Z, 1.0f / _JumpMidTime * _JumpPercent, 2);
		}
		else if (_JumpPercent > _JumpMidTime) {
			float timeleft = 1.0f - _JumpMidTime;
			float latertime = _JumpPercent - _JumpMidTime;
			Z = FMath::InterpEaseIn(_JumpMidPosition.Z, _JumpEndPosition.Z, 1.0f / timeleft * latertime, 2);
		}
		else {
			Z = _JumpMidPosition.Z; //extremely unlikely, but still possible.
		}



		CurrentPosition = FVector(XY.X, XY.Y, Z);
	}
	
	SetActorLocationAndRotation(CurrentPosition+FVector(0, 0, _PlayerHeight), _JumpAngle, false, nullptr, ETeleportType::None);


}

