// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerGameDoor.generated.h"

UCLASS()
class TGP_API APlatformerGameDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerGameDoor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotateAmount;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SlideAmount;

	bool bIsOpening;

	FRotator StartRotation, EndRotation, DifferenceRotation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveToSetRotation();
	void MoveToStartRotation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
