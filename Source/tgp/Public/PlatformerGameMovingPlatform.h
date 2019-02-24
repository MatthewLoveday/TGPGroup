// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerGameMovingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class TGP_API APlatformerGameMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerGameMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementDirection;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed;


	FVector StartLocation, EndLocation, Difference;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MovePlatformToEndLocation();
	void MovePlatformToStartLocation();
	
	
};
