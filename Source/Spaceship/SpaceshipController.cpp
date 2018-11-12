// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipController.h"
#include "Engine.h"

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
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);

	float ScreenX, ScreenY;
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	ScreenX = ViewportSize.X;
	ScreenY = ViewportSize.Y;

	return FVector2D(MouseX/ScreenX, MouseY/ScreenY);
}

void ASpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString MouseLocation = GetMouseCoordinates().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, MouseLocation);
}
