// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerSpawner.generated.h"

UCLASS()
class TGP_API APlatformerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual AActor* SpawnActor(TSubclassOf<AActor> BPToSpawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
