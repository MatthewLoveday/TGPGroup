// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Public/Containers/Array.h"
#include "MovingPlatform.generated.h"

UCLASS()
class TGP_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
private:
	int currIndex = 0;
	int dirModifier = 1;
	float t = 0;
	FVector startPos;
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> waypoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float movementSpeed = 1.0f;

	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
