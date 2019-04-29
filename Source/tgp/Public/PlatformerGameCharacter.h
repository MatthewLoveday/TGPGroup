// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "tgp.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "PlatformerGameSafetyNet.h"
#include "PlatformerGameCharacter.generated.h"


UCLASS(BlueprintType)
class TGP_API APlatformerGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;	

public:
	// Sets default values for this character's properties
	APlatformerGameCharacter();

	UFUNCTION(BlueprintCallable)
	void ChangeMoveset(EMovesetEnum newMoveSet);

	UFUNCTION(BlueprintCallable)
	EMovesetEnum GetMoveset() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Respawn();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool alive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Collectables")
	int CollectableCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Collectables")
	int BrokenChainCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Collectables")
	int OptionalCollectableCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Respawn")
		 APlatformerGameSafetyNet* SafetyNetRef;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moveset)
	EMovesetEnum moveSet;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EnterDefaultMoveSet();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EnterHeliMoveSet();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EnterBalloonMoveSet();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExitDefaultMoveSet();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExitHeliMoveSet();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExitBalloonMoveSet();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FHitResult PerformWallTrace(ECollisionChannel traceChannel = ECC_GameTraceChannel1, float ZOffset = 0.0f, float length = 50.0f, bool DrawTrace = false, bool invert = false);

	UFUNCTION(BlueprintCallable)
	FHitResult PerformCircleTrace(ECollisionChannel traceChannel = ECC_GameTraceChannel1, float ZOffset = 0.0f, float radius = 60.0f, bool DrawDebug = false);

	void IncrementCollectableCount() { CollectableCount++; }
};

