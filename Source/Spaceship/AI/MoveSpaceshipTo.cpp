// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveSpaceshipTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceshipPawn.h"

EBTNodeResult::Type UMoveSpaceshipTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the Pawn and convert to Spaceship
	ControlledSpaceship = Cast<ASpaceshipPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if(!ensure(ControlledSpaceship))
	{
		return EBTNodeResult::Failed;
	}

	ControlledSpaceship->SetMovingTowardsWayPoint(true);

	// Get the Waypoint
	UBlackboardComponent * BlackboardComponent = OwnerComp.GetBlackboardComponent();

	Waypoint = BlackboardComponent->GetValueAsVector(WaypointKey.SelectedKeyName);

	bNotifyTick = true;

	return EBTNodeResult::InProgress;
	
}

void UMoveSpaceshipTo::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	bNotifyTaskFinished = true;

	//ControlledSpaceship->MoveTowardsWaypoint();

	// Check if distance to waypoint is within acceptable distance
	float OutDistance;
	FVector OutDir;
	(ControlledSpaceship->GetActorLocation() - Waypoint).ToDirectionAndLength(OutDir, OutDistance);

	if (OutDistance < AcceptanceRadius)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UMoveSpaceshipTo::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	ControlledSpaceship->SetMovingTowardsWayPoint(false);
}

