// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipController.h"

void ASpaceshipController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);
}

FVector2D ASpaceshipController::GetMouseCoordinates()
{
	return FVector2D();
}

void ASpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
