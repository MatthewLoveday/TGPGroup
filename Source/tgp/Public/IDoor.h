// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDoor.generated.h"

UCLASS()
class TGP_API AIDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SlideDoorOpen();
	void SlideDoorClose();

	void RotateDoorOpen();
	void RotateDoorClose();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector DistanceToMove;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0"))
	FRotator DistanceToRotate;

	FVector StartLocation, DistanceToEndLoc, EndLocation;
	FRotator StartRotation, DistanceToEndRot, EndRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	bool CanOpen;

	UPROPERTY(BlueprintReadWrite)
	bool CanRotate;
	
	UPROPERTY(BlueprintReadWrite)
	bool MoveToStartLocation;

	UPROPERTY(BlueprintReadWrite)
	bool MoveToStartRotation;
};
