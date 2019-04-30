// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"

#include "PlatformerGameCharacter.h"
#include "Runtime/AIModule/Classes/Navigation/NavLinkProxy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyBaseCharacter.h"
#include "EnemyController.generated.h"


/**
 *
 */

UENUM(BlueprintType)
enum class EMoveState : uint8
{
	Spawning	UMETA(DisplayName = "Spawning"),
	Idle		UMETA(DisplayName = "Idle"),
	Roaming		UMETA(DisplayName = "Roaming"),
	Chasing		UMETA(DisplayName = "Chasing"),
	Frozen		UMETA(DisplayName = "Frozen"),
	Sleeping	UMETA(DisplayName = "Sleeping"),
	Returning	UMETA(DisplayName = "Returning"),
};
UENUM(BlueprintType)
enum class ENextAction : uint8 {
	Nothing = 0 UMETA(DisplayName = "Nothing"),
	NextWaypoint UMETA(DisplayName = "Find Next Waypoint"),
	ReturnToWaypoint UMETA(DisplayName = "Find Next Waypoint"),
	ReturnToLastLocation UMETA(DisplayName = "Go To Last Position")
};


UCLASS()
class TGP_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	bool CanWalkTo(FVector Position);

	void SetWalkSpeed(float speed);

	void ChasePlayer(APlatformerGameCharacter * Player);

	

	


	//UPROPERTY(BlueprintAssignable, Category = "SmartLinkBehaviour")
	//FSmartLinkReachedSignature OnSmartLinkReached;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		EMoveState MoveState = EMoveState::Spawning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		bool Running = false;

private:

	AEnemyBaseCharacter * Character;

	TArray<APlatformerGameCharacter *> Players;
	//APlatformerGameCharacter* _ClosestPlayer;
	//TArray<AActor*> Waypoints;

	ENextAction NextAction = ENextAction::Nothing;
	bool agro = false;
	float idletime = 0.0f;

//UFUNCTION()
	//ATargetPoint* GetRandomWaypoint();

	UFUNCTION()
		void GoToWaypoint();

	APlatformerGameCharacter * GetNearbyPlayer(float & Distance);
	bool CanSeePlayer(APlatformerGameCharacter * Player);

	//UFUNCTION(BlueprintCallable, Category = "SmartLinkBehaviour")
		//void SmartLinkTraverse();


};
