// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveSpaceshipTowardsActor.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API UMoveSpaceshipTowardsActor : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetActorKey;

	class ASpaceshipPawn * ControlledSpaceship;

	AActor * TargetActor;
};
