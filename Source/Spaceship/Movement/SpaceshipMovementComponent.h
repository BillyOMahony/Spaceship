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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

private:
	/*
	 *
	 */
	void MoveForward(float DeltaTime);

	/*
	 *
	 */
	void Stabilise();

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
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UMainThruster>> MainThrusters;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<USecondaryThruster>> SecondaryThrusters;

	UStaticMeshComponent * SpaceshipHull;

	bool ThrottleUpPressed = false;

	bool ThrottleDownPressed = false;
};
