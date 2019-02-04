// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SpaceshipAimTowardsTarget.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API USpaceshipAimTowardsTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	class ASpaceshipPawn * ControlledSpaceship;
};
