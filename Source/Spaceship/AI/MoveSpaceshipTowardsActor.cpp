// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveSpaceshipTowardsActor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceshipPawn.h"

EBTNodeResult::Type UMoveSpaceshipTowardsActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the Pawn and convert to Spaceship
	ControlledSpaceship = Cast<ASpaceshipPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ensure(ControlledSpaceship))
	{
		return EBTNodeResult::Failed;
	}

	// Get the Waypoint
	UBlackboardComponent * BlackboardComponent = OwnerComp.GetBlackboardComponent();

	TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));

	//ControlledSpaceship->SetWayPoint(TargetActor->GetActorLocation());
	ControlledSpaceship->SetMovingTowardsWayPoint(false);
	ControlledSpaceship->SetTargetActor(TargetActor);

	return EBTNodeResult::InProgress;
}