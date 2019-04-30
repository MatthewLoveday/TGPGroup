// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
	

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	if (Character == nullptr) {
		Character = Cast<AEnemyBaseCharacter>(GetPawn());
	}
	if (Character != nullptr) {
		GoToWaypoint();

		Character->LastNavPosition = Character->GetActorLocation();
		SetWalkSpeed(Character->Walk_Speed);
	} 
}


void AEnemyController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (Character == nullptr) {
		Character = Cast<AEnemyBaseCharacter>(GetPawn());
	}
	if (Character != nullptr) {
		//double check, just in case
		if (MoveState == EMoveState::Spawning) {
			//do spawn stuff??
			if (Character->Lifetime > 1) {
				MoveState = EMoveState::Idle;
			}
		}
		else {
			if (MoveState == EMoveState::Idle) {
				idletime += DeltaTime;
			}
			if (Character->MoveType == EMoveType::Simple || Character->MoveType == EMoveType::Complex) {
				if (MoveState == EMoveState::Idle) {
					//0 = nothing
					//1 = next waypoint
					//2 = return to previously targeted waypoint
					//3 = return to last location we were in before agro
					if (idletime >= 2.0f) {
						idletime = 0;
						int numPoints = Character->Walk_Points.Num();
						switch (NextAction) {
						case ENextAction::Nothing:
							//nothing
							break;
						case ENextAction::NextWaypoint:
							//next waypoint
							if (numPoints > 1) {
								int NewWaypoint = Character->CurrentWaypoint;
								switch (Character->WalkType) {
								case ENodeTraversal::Forward:
									NewWaypoint = (Character->CurrentWaypoint + 1) % (numPoints);
									break;
								case ENodeTraversal::Backwards:
									if (Character->CurrentWaypoint - 1 < 0) {
										NewWaypoint = numPoints - 1;
									}
									else {
										NewWaypoint = Character->CurrentWaypoint - 1;
									}
										
									break;
								case ENodeTraversal::Alternating:
									if (Character->CurrentWaypoint == numPoints - 1) {
										NewWaypoint = Character->CurrentWaypoint - 1;
										Character->AlternationState = false;
									}
									else if (Character->CurrentWaypoint == 0) {
										NewWaypoint = Character->CurrentWaypoint + 1;
										Character->AlternationState = true;
									}
									else {
										//somewhere inbetween, won't happen if there's only 2 nodes
										if (Character->AlternationState) {
											//forward
											NewWaypoint = Character->CurrentWaypoint + 1;
										}
										else {
											//backwards
											NewWaypoint = Character->CurrentWaypoint - 1;
										}
									}
									break;
								case ENodeTraversal::Random:
									if (numPoints == 2) {
										NewWaypoint = 1 - Character->CurrentWaypoint; // basically alternating.
									}
									else {
										//do while loop ensures it eventually lands on a different value;
										do {
											NewWaypoint = FMath::RoundToInt(FMath::FRand()*numPoints);
										} while (NewWaypoint == Character->CurrentWaypoint);
										break;
									}
								}
								Character->CurrentWaypoint = NewWaypoint;
								if (Character->CurrentWaypoint < numPoints && Character->CurrentWaypoint >= 0) {
									MoveToActor(Character->Walk_Points[Character->CurrentWaypoint]);
								}
								else {
									Character->CurrentWaypoint = 0;
									MoveToActor(Character->Walk_Points[0]);
								}
								MoveState = EMoveState::Roaming;
							}
							else {
								Character->CurrentWaypoint = 0;
							}
							break;
						case ENextAction::ReturnToWaypoint:
							//2 = return to previously targeted waypoint
							agro = false; //we are no longer off-path, so no longer agro
							GoToWaypoint();
							break;

						case ENextAction::ReturnToLastLocation:
							//stopped chasing player, return to last place was at
							MoveState = EMoveState::Returning;
							if (Character->LastNavPosition != FVector(0,0,0)) {
								MoveToLocation(Character->LastNavPosition);
							}
							break;
						default:

							break;
						}
					} // idletime>2
				}
				else {//not idle
					
					//roaming or something

				}
			}
			if (Players.Num() == 0) {
				TArray< AActor*> PlayerList;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlatformerGameCharacter::StaticClass(), PlayerList);
				if (PlayerList.Num() > 0) {
					for (int i = 0; i < PlayerList.Num(); i++) {
						AActor* A = PlayerList[i];
						APlatformerGameCharacter* Player = Cast<APlatformerGameCharacter>(A);
						if (Player != nullptr) {
							Players.Add(Player);
						}
					}
				}
				//todo: find nearest player(s), assign if null
			}
			
			float PlayerDistance = Character->Agro_Range;
			if (MoveState == EMoveState::Chasing) {
				PlayerDistance = Character->De_Agro_Range;
			}
			APlatformerGameCharacter* Player = GetNearbyPlayer(PlayerDistance);
			if (Player != nullptr) {
				UE_LOG(LogTemp, Verbose, TEXT("PLAYER"));
				//raytrace to player
				if (CanSeePlayer(Player)) {
					//chase player
					if (Character->MoveType == EMoveType::Stationary) {
						//try to hit if in range
						if (PlayerDistance < 100) {
							//play hit animation, if there is one
						}
					}
					else {
						ChasePlayer(Player);
					}
				}
			}
		}
	}

	

	//every tick, check if they are near or whatever, depending on enemy type, chase and/or attack, remember position before chasing player
	//depending on attack type try to attack if player is within reach
	//if chasing, remember last place seen and go towards it
	//if player not found once reaching last seen position, wait a moment before returning to last position
	//once reach original position, return to intended patrol.
}


bool AEnemyController::CanWalkTo(FVector Position) {
	UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navSys) {
		UNavigationPath* path = navSys->FindPathToLocationSynchronously(GetWorld(), GetPawn()->GetActorLocation(), Position);
		return path->IsValid();
	}
	else {
		return false;
	}
}

void AEnemyController::SetWalkSpeed(float speed) {
	UCharacterMovementComponent * CMoveComp = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	CMoveComp->MaxWalkSpeed = speed;
}

void AEnemyController::ChasePlayer(APlatformerGameCharacter* Player) {
	if (Player != nullptr) {
		FVector PlayerPosition = Player->GetActorLocation();


		//UNavigationPath* path = navSys->FindPathSync()
		if (CanWalkTo(PlayerPosition)) {

			//FVector End = PlayerPosition + FVector(0,0,-600.0);
			//FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
			//RV_TraceParams.bTraceComplex = false;
			//RV_TraceParams.bTraceAsyncScene = false;
			//RV_TraceParams.bReturnPhysicalMaterial = false;
			//const FName TraceTag("MyTraceTag");
			//RV_TraceParams.TraceTag = TraceTag;
			//FHitResult RV_Hit;

			//DrawDebugLine(GetWorld(), PlayerPosition, End, FColor::Green, false, 1, 0, 5);

			//bool Success = GetWorld()->LineTraceSingleByChannel(RV_Hit, PlayerPosition, End, ECC_EngineTraceChannel1, RV_TraceParams);
			//if (Success) {
				//UE_LOG(LogTemp, Verbose, TEXT("HIT DETECTED"));
				//FVector HitPos = RV_Hit.ImpactPoint;

				//UE_LOG(LogTemp, Verbose, TEXT("SETTING INFO"));
			if (agro == false) {
				Character->LastNavPosition = Character->GetActorLocation();
				agro = true;
			}
			SetWalkSpeed(Character->Run_Speed);
			Running = true;
			MoveState = EMoveState::Chasing;

			//UE_LOG(LogTemp, Verbose, TEXT("GOING TO POSITION"));
			//MoveToLocation(HitPos);

			MoveToLocation(PlayerPosition);
			//UE_LOG(LogTemp, Verbose, TEXT("POSITION-GOTO SUCCESS"));
		//}
		//else {
			//act like it wasn't called?
		//}
		}
	}
}

bool AEnemyController::CanSeePlayer(APlatformerGameCharacter* Player) {
	return true;
}
//Input max distance (reference), uses same variable to return distance of player
APlatformerGameCharacter* AEnemyController::GetNearbyPlayer(float &Distance) {
	APlatformerGameCharacter* ClosestPlayer = nullptr;
	if (Players.Num() > 0) {
		FVector MyPosition = Character->GetActorLocation();
		float ClosestDistance = Distance;
		for (int i = 0; i < Players.Num(); i++) {
			APlatformerGameCharacter* Player = Players[i];
			FVector TheirPosition = Player->GetActorLocation();
			FVector Difference = TheirPosition - MyPosition;
			FVector Direction; float NewDistance;
			Difference.ToDirectionAndLength(Direction, NewDistance);
			if (NewDistance < ClosestDistance) {
				//DrawDebugLine(GetWorld(), MyPosition, TheirPosition, FColor(255, 0, 0), true, 10.0f, 0, 1.0f);
				ClosestDistance = NewDistance;
				ClosestPlayer = Player;
			}
		}
		Distance = ClosestDistance;
		return ClosestPlayer;
	}
	else {
		return nullptr;
	}
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
	if (Character != nullptr) {
		int numPoints = Character->Walk_Points.Num();
		if (numPoints > 0) {
			if (Character->CurrentWaypoint < numPoints && Character->CurrentWaypoint>=0) {
				AActor * Target = Character->Walk_Points[Character->CurrentWaypoint];
				if (Target != nullptr) {
					if (CanWalkTo(Target->GetActorLocation())) {
						MoveToActor(Target);
					}
				}
			}
			else {
				AActor * Target = Character->Walk_Points[0];
				if (Target != nullptr) {
					MoveToActor(Character->Walk_Points[0]);
					if (CanWalkTo(Target->GetActorLocation())) {
						MoveToActor(Target);
					}
				}
			}
			MoveState = EMoveState::Roaming;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No Nodes to go to"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Character"));
	}
}
/*
void AEnemyController::SmartLinkTraverse()
{

}*/

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	UE_LOG(LogTemp, Verbose, TEXT("NodeReached"));
	if (Character != nullptr) {
		if (Character->MoveType != EMoveType::Stationary) {
			//MoveState is the cause of hitting this pointer
			if (MoveState == EMoveState::Chasing) {
				Running = false;
				SetWalkSpeed(Character->Walk_Speed);
				//reached player position?
				float PlayerDistance = Character->De_Agro_Range;
				APlatformerGameCharacter* Player = GetNearbyPlayer(PlayerDistance);
				if (Player == nullptr) {
					//return
					MoveState = EMoveState::Idle;
					NextAction = ENextAction::ReturnToLastLocation;
				}
				else {
					//raytrace to player to see if within sight
					if (CanSeePlayer(Player)) {
						ChasePlayer(Player);
					}
				}
				
				//if player not within range

			}
			else if (MoveState == EMoveState::Returning) {
				//was returning to this position, therefore continue route
				MoveState = EMoveState::Idle;
				NextAction = ENextAction::ReturnToWaypoint;
			}
			else if (MoveState == EMoveState::Roaming) {
				MoveState = EMoveState::Idle;
				NextAction = ENextAction::NextWaypoint;
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Character"));
	}

}
