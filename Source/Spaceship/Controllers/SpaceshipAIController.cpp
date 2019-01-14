// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipAIController.h"
#include "SpaceshipPawn.h"


void ASpaceshipAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardsWaypointActor();
}

void ASpaceshipAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = Cast<ASpaceshipPawn>(GetPawn());
}

void ASpaceshipAIController::MoveTowardsWaypointActor()
{
	if(ControlledPawn)
	{
		ControlledPawn->MoveTowardsWaypoint();
	}
}
