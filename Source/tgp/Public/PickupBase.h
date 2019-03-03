// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class TGP_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent *SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase *OverlapSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystemComponent *CollectEffect;

	int RotationSpeed;
	FRotator CurrentRotation;

	void RotateActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
