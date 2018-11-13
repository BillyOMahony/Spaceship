// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/SpaceshipThrusterComponent.h"
#include "MainThruster.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACESHIP_API UMainThruster : public USpaceshipThrusterComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 *	@param Hull - The static mesh component which represents the main body of this spaceship
	 */
	UFUNCTION(BlueprintCallable)
	void SetSpaceshipHull(UStaticMeshComponent * Hull);

	UFUNCTION(BlueprintCallable)
	void AddThrottle(float ThrottleToAdd);

	void AccelerateSpaceship(float DeltaTime);

private:
	UPROPERTY(EditAnywhere)
	float Throttle = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxVelocity = 10000.f;

	UPROPERTY(EditAnywhere)
	float AccelerationForce = 1000000.f;

	UPROPERTY(EditAnywhere)
	bool InvertAcceleration = true;

	UStaticMeshComponent * SpaceshipHull;

};
