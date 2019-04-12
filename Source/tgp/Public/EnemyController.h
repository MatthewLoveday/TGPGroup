// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/AIModule/Classes/Navigation/NavLinkProxy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyBaseCharacter.h"
#include "EnemyController.generated.h"


/**
 *
 */

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


UCLASS()
class TGP_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;


	//UPROPERTY(BlueprintAssignable, Category = "SmartLinkBehaviour")
	//FSmartLinkReachedSignature OnSmartLinkReached;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;


private:
	//UPROPERTY()
	AEnemyBaseCharacter * Character;
	//TArray<AActor*> Waypoints;

//UFUNCTION()
	//ATargetPoint* GetRandomWaypoint();

	UFUNCTION()
		void GoToWaypoint();

	//UFUNCTION(BlueprintCallable, Category = "SmartLinkBehaviour")
		//void SmartLinkTraverse();


};
