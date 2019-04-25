// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "tgp.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerGameSafetyNet.generated.h"

class UBoxComponent;

UCLASS()
class TGP_API APlatformerGameSafetyNet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerGameSafetyNet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent *CollisionComp;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
					   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
					   bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, Category = "Teleport Options")
	FVector TeleportLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTeleportLocation(const FVector& newLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovesetEnum CachedMoveset;
};
