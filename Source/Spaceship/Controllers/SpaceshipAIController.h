// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SpaceshipAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API ASpaceshipAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	/*
	 *	Moves the pawn towards a point in space
	 */
	void MoveTowardsPoint(FVector Point);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/*
	 *	Aims towards and fires at an actor
	 */
	void AimTowardAndFireAtTargetActor();

	class ASpaceshipPawn * ControlledPawn = nullptr;
};
