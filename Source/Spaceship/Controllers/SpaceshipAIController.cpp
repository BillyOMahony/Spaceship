// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipAIController.h"
#include "SpaceshipPawn.h"


void ASpaceshipAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AimTowardAndFireAtTargetActor();
}

void ASpaceshipAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = Cast<ASpaceshipPawn>(GetPawn());
	ControlledPawn->SetAIControlsPawn(true);
}

void ASpaceshipAIController::AimTowardAndFireAtTargetActor()
{
	if (ControlledPawn)
	{
		ControlledPawn->AimTowardsTarget();
	}
}
