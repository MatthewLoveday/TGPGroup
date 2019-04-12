// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "PlatformerGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyBaseCharacter.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENodeTraversal : uint8
{
	Forward 	UMETA(DisplayName = "Forward"),
	Backwards 	UMETA(DisplayName = "Backwards"),
	Alternating	UMETA(DisplayName = "Alternating"),
	Random		UMETA(DisplayName = "Random")
};


enum class EMoveType :uint8 {
	Complex UMETA(DisplayName = "Complex"),
	Simple UMETA(DisplayName = "Complex"),
	Stationary UMETA(DisplayName = "Complex"),
};


UCLASS()
class TGP_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();


	EMoveType MoveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Walk Nodes")
		TArray<ATargetPoint*> Walk_Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Walk Nodes")
		int CurrentWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Walk Nodes")
		ENodeTraversal Walk = ENodeTraversal::Random;


	UFUNCTION(BlueprintCallable, Category = "Character Movement: Walk Nodes")
		void NavJumpTo(FVector Destination);



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Walk Nodes")
		bool Jumping;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual void ComplexUpdate(float DeltaTime);

	//virtual void SimpleUpdate(float DeltaTime);

	//virtual void StationaryUpdate(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	APlatformerGameCharacter * Player;

	FVector _JumpStartPosition;
	FVector _JumpMidPosition;
	FVector _JumpEndPosition;
	FQuat _JumpAngle;
	float _JumpSpacing; //the minimum amount of elevation above the start or end position to jump
	float _JumpTime;
	float _JumpMidTime;
	float _JumpDuration; //the distance between the jump, to measure time it takes to perform jump

	//EMoveState _MoveState;


	void JumpTransition(float DeltaTime);
};
