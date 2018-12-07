// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonSpaceshipController.h"
#include "Engine.h"
#include "Movement/SpaceshipMovementComponent.h"
#include "Weapon/SpaceshipWeaponsComponent.h"

void AFirstPersonSpaceshipController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);

	MovementComponent = GetPawn()->FindComponentByClass<USpaceshipMovementComponent>();
	if (!MovementComponent) UE_LOG(LogTemp, Error, TEXT("ASpaceshipController - MovementComponent not found"));
}

void AFirstPersonSpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InputPitch(DeltaTime);
	InputYaw(DeltaTime);

	AimTowardsCrosshair();
}

FVector2D AFirstPersonSpaceshipController::GetMouseCoordinates() const
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);

	float ScreenX, ScreenY;
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	ScreenX = ViewportSize.X;
	ScreenY = ViewportSize.Y;

	return FVector2D(MouseX / ScreenX, MouseY / ScreenY);
}

void AFirstPersonSpaceshipController::InputPitch(float DeltaTime)
{
	FVector2D Rotation2DVector = GetMousePositionRelativeToCenter();

	if (Rotation2DVector.Y > MousePositionTolerance || Rotation2DVector.Y < -MousePositionTolerance) {

		float newY;

		if (Rotation2DVector.Y > MousePositionTolerance) newY = Rotation2DVector.Y - MousePositionTolerance;
		else newY = Rotation2DVector.Y + MousePositionTolerance;

		float PitchMultiplier = newY / (1 - MousePositionTolerance);

		MovementComponent->Pitch(DeltaTime, PitchMultiplier);
	}
}

void AFirstPersonSpaceshipController::InputYaw(float DeltaTime)
{

	FVector2D Rotation2DVector = GetMousePositionRelativeToCenter();

	if (Rotation2DVector.X > MousePositionTolerance || Rotation2DVector.X < -MousePositionTolerance) {

		float newX;

		if (Rotation2DVector.X > MousePositionTolerance) newX = Rotation2DVector.X - MousePositionTolerance;
		else newX = Rotation2DVector.X + MousePositionTolerance;

		float YawMultiplier = newX / (1 - MousePositionTolerance);

		MovementComponent->Yaw(DeltaTime, YawMultiplier);
	}
}

bool AFirstPersonSpaceshipController::GetCrosshairDirection(FVector & LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectMousePositionToWorld(CameraWorldLocation, LookDirection);
}

bool AFirstPersonSpaceshipController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = GetMouseCoordinates();

	FVector LookDirection;
	if (GetCrosshairDirection(LookDirection)) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
		return true;
	}

	//Line trace along that look direction and see what we hit (up to max range)
	return false;
}

void AFirstPersonSpaceshipController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + (LookDirection * LineTraceRange), ECollisionChannel::ECC_Camera)) {
		//Set Hit Location
		HitLocation = HitResult.Location;
		if (HitResult.GetActor() != GetPawn()) return;
	}
	HitLocation = StartLocation + (LookDirection * LineTraceRange);
}

void AFirstPersonSpaceshipController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // if not possessing 
	WeaponsComponent = GetPawn()->FindComponentByClass<USpaceshipWeaponsComponent>();
	if (!ensure(WeaponsComponent)) { return; }

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (GetSightRayHitLocation(HitLocation)) {
		WeaponsComponent->AimAt(HitLocation);
	}
}

FVector2D AFirstPersonSpaceshipController::GetMousePositionRelativeToCenter()
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
