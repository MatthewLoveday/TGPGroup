// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "PlatformerGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyBaseCharacter.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENodeTraversal : uint8 {
	Forward 	UMETA(DisplayName = "Forward"),
	Backwards 	UMETA(DisplayName = "Backwards"),
	Alternating	UMETA(DisplayName = "Alternating"),
	Random		UMETA(DisplayName = "Random")
};

UENUM(BlueprintType)
enum class EMoveType :uint8 {
	Stationary	UMETA(DisplayName = "Stationary"),
	Simple		UMETA(DisplayName = "Simple"),
	Complex		UMETA(DisplayName = "Complex")
};

UENUM(BlueprintType)
enum class EAttackType :uint8 {
	None		UMETA(DisplayName = "None"),
	Melee		UMETA(DisplayName = "Melee"),
	Ranged		UMETA(DisplayName = "Ranged")

};

UENUM(BlueprintType)
enum class EChaseType :uint8 {
	Yes		UMETA(DisplayName = "Do Chase"),
	No		UMETA(DisplayName = "Don't Chase")
};

UCLASS()
class TGP_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TArray<ATargetPoint*> Walk_Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int CurrentWaypoint = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		ENodeTraversal WalkType = ENodeTraversal::Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		EMoveType MoveType = EMoveType::Stationary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		EAttackType AttackType = EAttackType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		EChaseType ChaseType = EChaseType::No;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float Agro_Range = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float De_Agro_Range = 500.0f;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
		void NavJumpTo(FVector Destination);



	UPROPERTY(BlueprintReadOnly, Category = "Enemy")
		bool Jumping = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float Lifetime = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual void StationaryUpdate(float DeltaTime);

	//virtual void SimpleUpdate(float DeltaTime);

	//virtual void ComplexUpdate(float DeltaTime);

	

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	APlatformerGameCharacter * Player;

	//Jumping variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	FVector _JumpStartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	FVector _JumpMidPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	FVector _JumpEndPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	FQuat _JumpAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	float _JumpSpacing = 70.0f;; //the minimum amount of elevation above the start or end position to jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	float _PlayerHeight = 40.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	float _JumpTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	float _JumpMidTime = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	float _JumpDuration = 1; //the distance between the jump, to measure time it takes to perform jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
	float _JumpPercent = 0;

	//true = forward, false = backwards
	bool AlternationState = true;
	//the position we were in when agro'd
	FVector LastNavPosition;
	//EMoveState _MoveState;
	

	void JumpTransition(float DeltaTime);

	
};
