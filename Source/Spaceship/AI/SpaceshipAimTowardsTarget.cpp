// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipAimTowardsTarget.h"
#include "SpaceshipPawn.h"
#include "AIController.h"

EBTNodeResult::Type USpaceshipAimTowardsTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControlledSpaceship = Cast<ASpaceshipPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ensure(ControlledSpaceship))
	{
		return EBTNodeResult::Failed;
	}

	ControlledSpaceship->AimTowardsTarget();

	return EBTNodeResult::Succeeded;
}
