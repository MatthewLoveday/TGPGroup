// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTriggerOpen.h"
#include "Components/BoxComponent.h"
#include "PlatformerGameCharacter.h"
#include "IDoor.h"

ADoorTriggerOpen::ADoorTriggerOpen()
{
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorTriggerOpen::HandleOverlap);
}

void ADoorTriggerOpen::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
									 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
									 bool bFromSweep, const FHitResult &SweepResult)
{
	APlatformerGameCharacter *myChar = Cast<APlatformerGameCharacter>(OtherActor);

	if (myChar)
	{
		for (int i = 0; i < doors.Num(); i++)
		{
			doors[i]->CanOpen = true;
			doors[i]->CanRotate = true;
		}
	}
}

