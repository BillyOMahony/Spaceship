// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/SpaceshipThrusterComponent.h"
#include "SecondaryThruster.generated.h"

/**
 *	The position of this thruster on the X axis relative to the center of the spaceship
 */
UENUM(BlueprintType)
enum class EThrusterPositionX {
	Front	UMETA(DisplayName = "Front"),
	Rear	UMETA(DisplayName = "Rear"),
	Center	UMETA(DisplayName = "Center")
}


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACESHIP_API USecondaryThruster : public USpaceshipThrusterComponent
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetThrottle(float Throttle);

	void AddForceInDirection();
};
