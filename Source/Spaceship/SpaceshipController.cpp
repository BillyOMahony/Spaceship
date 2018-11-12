// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipController.h"

void ASpaceshipController::BeginPlay()
{
	Super::BeginPlay();
	// Shows the mouse cursor
	bShowMouseCursor = true;
}

void ASpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
