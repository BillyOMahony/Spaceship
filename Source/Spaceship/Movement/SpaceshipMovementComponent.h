// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceshipMovementComponent.generated.h"

class UMainThruster;
class USecondaryThruster;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API USpaceshipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceshipMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void HandleThrustInputs(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 *	@param SpaceshipHull - The spaceship hull which forces will be applied to
	 */
	UFUNCTION(BlueprintCallable)
	void SetSpaceshipHull(UStaticMeshComponent * SpaceshipHull);

	/*
	 *	Accelerates the Spaceship if possible
	 *	@param DeltaTime - Time since last frame
	 */
	UFUNCTION(BlueprintCallable)
	void ThrottleUp(float DeltaTime, float Multiplier);

	/*
	 *	Decelerated the spaceship if possible
	 *	@param DeltaTime - Time since last frame
	 */
	UFUNCTION(BlueprintCallable)
	void ThrottleDown(float DeltaTime, float Multiplier);

	/*
	*  @param ThrustUpPressed - Whether or not the ThrustUp input key is pressed
	*/
	UFUNCTION(BlueprintCallable)
	void SetThrustUpPressed(bool ThrustUpPressed);

	/*
	*  @param ThrustDownPressed - Whether or not the ThrustDown input key is pressed
	*/
	UFUNCTION(BlueprintCallable)
	void SetThrustDownPressed(bool ThrustDownPressed);

	/*
	*  @param ThrustLeftPressed - Whether or not the ThrustLeft input key is pressed
	*/
	UFUNCTION(BlueprintCallable)
	void SetThrustLeftPressed(bool ThrustLeftPressed);

	/*
	*  @param ThrustRightPressed - Whether or not the ThrustRight input key is pressed
	*/
	UFUNCTION(BlueprintCallable)
	void SetThrustRightPressed(bool ThrustRightPressed);

	/*
	 *	Pitches the spaceship
	 *	@param DeltaTime - Time since last frame
	 *	@param Multiplier - controls direction of pitch and acts as a multiplier
	 */
	UFUNCTION(BlueprintCallable)
	void Pitch(float DeltaTime, float Multiplier);

	/*
	 *	Yaws the spaceship	
	 *	@param DeltaTime - Time since last frame
	 *	@param Multiplier - controls direction of yaw and acts as a multiplier
	*/
	UFUNCTION(BlueprintCallable)
	void Yaw(float DeltaTime, float Multiplier);

	/*
	*	Rolls the spaceship
	*	@param DeltaTime - Time since last frame
	*	@param Multiplier - controls direction of roll and acts as a multiplier
	*/
	UFUNCTION(BlueprintCallable)
	void Roll(float DeltaTime, float Multiplier);

	/*
	 *	@return Current Throttle of spaceship
	 */
	UFUNCTION(BlueprintCallable)
	float GetMainThrottle();

	/*
	 *	@return Velocity of spaceship
	 */
	UFUNCTION(BlueprintCallable)
	float GetForwardVelocity();

	/*
	 *	Rolls the spaceship, but will not roll beyond a certain angle
	 */
	void CappedRoll(float DeltaTime, float RollPosition);

private:

	/*
	 *	Finds all MainThruster Components of this actor and adds them to the MainThrusters array
	 */
	void PopulateMainThrusters();

	/*
	 *	Finds all SecondaryThruster Components of this actor and adds them to the SecondaryThrusters array
	 */
	void PopulateSecondaryThrusters();

	/*
	 *	Instructs all Main Thrusters to accelerate
	 */
	void MoveForward(float DeltaTime);

	/*
	 *	Automatically fires thrusters to stabalize the spaceship on the left/right and up/down axes if there is no current input for those axes.
	 */
	void Stabilize(float DeltaTime);

	/*
	 *	Adds to MainThrottle
	 *	Clamps value between 0 and 1
	 *	@param ThrottleToAdd - the throttle to add to MainThrottle
	 */
	void AddMainThrottle(float ThrottleToAdd);

	UPROPERTY(EditAnywhere)
	float MainThrottleChangeMultiplier = 0.25;

	UPROPERTY(EditAnywhere)
	float RollPerSec = 75;

	UPROPERTY(EditAnywhere)
	float PitchPerSec = 45;

	UPROPERTY(EditAnywhere)
	float YawPerSec = 20;

	float MainThrottle = 0;
	
	TArray<UMainThruster *> MainThrusters;

	TArray<USecondaryThruster *> SecondaryThrusters;

	UStaticMeshComponent * SpaceshipHull;

	bool ThrottleUpPressed = false;

	bool ThrottleDownPressed = false;

	bool ThrustUpPressed = false;

	bool ThrustDownPressed = false;

	bool ThrustLeftPressed = false;

	bool ThrustRightPressed = false;
};
