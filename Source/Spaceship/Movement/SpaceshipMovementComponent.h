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
	 *	Tick Function designed to be called directly from bluepring
	 */
	UFUNCTION(BlueprintCallable)
	void TickSubstitute(float DeltaTime);

	/*
	 *	@param SpaceshipHull - The spaceship hull which forces will be applied to
	 */
	UFUNCTION(BlueprintCallable)
	void SetSpaceshipHull(UStaticMeshComponent * SpaceshipHull);

	/*
	 *  @param ThrottleUpPressed - Whether or not the ThrottleUp input key is pressed 
	 */
	UFUNCTION(BlueprintCallable)
	void SetThrottleUpPressed(bool ThrottleUpPressed);

	/*
	 *  @param ThrottleUpPressed - Whether or not the ThrottleDown input key is pressed 
	 */
	UFUNCTION(BlueprintCallable)
	void SetThrottleDownPressed(bool ThrottleDownPressed);

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
	 *
	 */
	void Stabilize(float DeltaTime);

	/*
	 *	Adds to MainThrottle
	 *	Clamps value between 0 and 1
	 *	@param ThrottleToAdd - the throttle to add to MainThrottle
	 */
	void AddMainThrottle(float ThrottleToAdd);

	/*
	 *	Increases or decreases Throttle if the relevant input key is pressed
	 *	@param DeltaTime - Time since last frame
	 */
	void HandleThrottle(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float MainThrottleChangeMultiplier = 0.25;

	float MainThrottle;
	
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
