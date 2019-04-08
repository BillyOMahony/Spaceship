// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipAimTowardsTarget.h"
#include "SpaceshipPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type USpaceshipAimTowardsTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControlledSpaceship = Cast<ASpaceshipPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ensure(ControlledSpaceship))
	{
		return EBTNodeResult::Failed;
	}

	// Get the Waypoint
	UBlackboardComponent * BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AActor * TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));

	ControlledSpaceship->AimTowardsTarget(TargetActor);

	return EBTNodeResult::Succeeded;
}
