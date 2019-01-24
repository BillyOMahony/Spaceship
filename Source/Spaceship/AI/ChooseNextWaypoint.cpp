// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points
	APawn * ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	UPatrolRoute * PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if(!ensure(PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}

	TArray<AActor *> PatrolPoints = PatrolRoute->GetPatrolPoints();

	if(PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points Found"));
		return EBTNodeResult::Failed;
	}

	// Get the blackboard and current point index
	UBlackboardComponent * BlackboardComponent = OwnerComp.GetBlackboardComponent();

	int Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);

	// Set Waypoint
	BlackboardComponent->SetValueAsVector(WaypointKey.SelectedKeyName, PatrolPoints[Index]->GetActorLocation());

	// Cycle Index
	Index++;
	Index = Index % PatrolPoints.Num();

	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
