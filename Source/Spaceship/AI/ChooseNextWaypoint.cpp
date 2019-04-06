// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceshipPawn.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points
	APawn * ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	UPatrolRoute * PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if(!PatrolRoute)
	{
		UE_LOG(LogTemp, Error, TEXT("UChooseNextWaypoint::ExecuteTask - No PatrolRoute class found on actor %s"), *(ControlledPawn->GetName()));
		return EBTNodeResult::Failed;
	}

	TArray<AActor *> PatrolPoints = PatrolRoute->GetPatrolPoints();

	if(PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UChooseNextWaypoint::ExecuteTask - No Patrol Points Found"));
		return EBTNodeResult::Failed;
	}

	// Get the blackboard and current point index
	UBlackboardComponent * BlackboardComponent = OwnerComp.GetBlackboardComponent();

	int Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);

	// Set Waypoint on blackboard
	BlackboardComponent->SetValueAsVector(WaypointKey.SelectedKeyName, PatrolPoints[Index]->GetActorLocation());

	// Set WayPoint on Spaceship
	ASpaceshipPawn * ControlledSpaceship = Cast<ASpaceshipPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ControlledSpaceship)
	{
		UE_LOG(LogTemp, Error, TEXT("UChooseNextWaypoint::ExecuteTask - Could not cast %s"), *(ControlledPawn->GetName()));
		return EBTNodeResult::Failed;
	}

	ControlledSpaceship->SetWayPoint(BlackboardComponent->GetValueAsVector(WaypointKey.SelectedKeyName));

	// Cycle Index
	Index++;
	Index = Index % PatrolPoints.Num();

	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
