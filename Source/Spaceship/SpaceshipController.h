// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceshipController.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API ASpaceshipController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	/*
	*	@return the location of the mouse relative to the center of the screen
	*/
	UFUNCTION(BlueprintCallable)
	FVector2D GetMousePositionRelativeToCenter();

protected:
	virtual void BeginPlay() override;

private:
	/*
	 *	@return the screen coordinates of the mouse as a percentage
	 */
	FVector2D GetMouseCoordinates() const;

	/*
	 *	Calculates pitch multiplier and calls the Pitch method of the SpaceshipMovementComponent
	 */
	void InputPitch(float DeltaTime);

	/*
	 *	Calculates yaw multiplier and calls the yaw method of the SpaceshipMovementComponent
	 */
	void InputYaw(float DeltaTime);

	/*
	*	Calculates yaw multiplier and calls the yaw method of the SpaceshipMovementComponent
	*/
	void InputRoll(float DeltaTime);

	/*
	 *	Deprojects the mouse position to world location
	 *	@param LookDirection - Out parameter - the direction the camera crosshair is pointing in
	 *	@return whether or not deprojection was successful
	 */
	bool GetCrosshairDirection(FVector &LookDirection) const;

	/*
	 *	
	 */
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	/*
	 *
	 */
	void GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

	/*
	 *
	 */
	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 50000.f;

	UPROPERTY(EditAnywhere)
	float MousePositionTolerance = .2;

	class USpaceshipMovementComponent * MovementComponent;

	class USpaceshipWeaponsComponent * WeaponsComponent;
};

