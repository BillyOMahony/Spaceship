// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipController.h"
#include "Engine.h"

void ASpaceshipController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);
}

FVector2D ASpaceshipController::GetMouseCoordinates()
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);

	float ScreenX, ScreenY;
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	ScreenX = ViewportSize.X;
	ScreenY = ViewportSize.Y;

	return FVector2D(MouseX/ScreenX, MouseY/ScreenY);
}

FVector2D ASpaceshipController::GetMousePositionRelativeToCenter()
{
	FVector2D MouseCoordinates = GetMouseCoordinates();

	float MouseX = MouseCoordinates.X;
	float MouseY = MouseCoordinates.Y;

	MouseX = (MouseX - .5) * 2;

	// Multiply by -2 to invert the values.
	// 1,1 will now
	MouseY = (MouseY - .5) * -2;

	return FVector2D(MouseX, MouseY);
}

void ASpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString MouseLocation = GetMousePositionRelativeToCenter().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, MouseLocation);
}
