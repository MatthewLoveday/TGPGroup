// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerInvisibleWalls.generated.h"

class UBoxComponent;

UCLASS()
class TGP_API APlatformerInvisibleWalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerInvisibleWalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent *CollisionComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
