// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	if (Character == nullptr) {
		Character = Cast<AEnemyBaseCharacter>(GetPawn());
	}

	//OnSmartLinkReached.AddDynamic(this, &AEnemyController::BeginJump);
}


/*
ATargetPoint* AEnemyController::GetRandomWaypoint()
{
	//auto max = Waypoints.Num();
	//if (max > 1) {
	//	auto index = 0;//FMath::RandRange(0,  - 1);
	//	return Cast<ATargetPoint>(Waypoints[index]);
	//}
	return nullptr;
}
*/
void AEnemyController::GoToWaypoint()
{
	//Character->MoveToWaypoint()
	//ATargetPoint* Waypoint = GetRandomWaypoint();
	//if (Waypoint != nullptr) {
	//	MoveToActor(Waypoint);
	//}

}
/*
void AEnemyController::SmartLinkTraverse()
{

}*/

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{


}
