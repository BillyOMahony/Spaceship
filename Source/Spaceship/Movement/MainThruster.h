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


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddThrottle(float ThrottleToAdd);

	void AccelerateSpaceship(float DeltaTime);

private:
	
};
