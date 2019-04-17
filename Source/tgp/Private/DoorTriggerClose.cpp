// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTriggerClose.h"
#include "Components/BoxComponent.h"
#include "PlatformerGameCharacter.h"
#include "IDoor.h"

ADoorTriggerClose::ADoorTriggerClose()
{
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorTriggerClose::HandleOverlap);
}

void ADoorTriggerClose::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *myChar = Cast<APlatformerGameCharacter>(OtherActor);

	if (myChar)
	{
		for (int i = 0; i < doors.Num(); i++)
		{
			doors[i]->MoveToStartLocation = true;
			doors[i]->MoveToStartRotation = true;
		}
	}
}


