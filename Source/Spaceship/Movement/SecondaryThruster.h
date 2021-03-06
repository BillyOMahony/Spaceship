// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/SpaceshipThrusterComponent.h"
#include "SecondaryThruster.generated.h"

/**
 *	The direction this thruster pushes the spaceship
 */
UENUM(BlueprintType)
enum class EThrustDirection : uint8 {
	Up		UMETA(DisplayName = "Up"),
	Down	UMETA(DisplayName = "Down"),
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right")
};

/**
 *	The position of this thruster on the X axis relative to the center of the spaceship
 */
UENUM(BlueprintType)
enum class EThrusterPositionX : uint8 {
	Front	UMETA(DisplayName = "Front"),
	Rear	UMETA(DisplayName = "Rear"),
	Center	UMETA(DisplayName = "Center")
};

/**
*	The position of this thruster on the Y axis relative to the center of the spaceship
*/
UENUM(BlueprintType)
enum class EThrusterPositionY : uint8 {
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
	Center	UMETA(DisplayName = "Center")
};

/**
*	The position of this thruster on the Z axis relative to the center of the spaceship
*/
UENUM(BlueprintType)
enum class EThrusterPositionZ : uint8 {
	Top	UMETA(DisplayName = "Top"),
	Bottom	UMETA(DisplayName = "Bottom"),
	Side	UMETA(DisplayName = "Side")
};

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

	/*
	 *	TODO
	 */
	void SetThrottle(float Throttle);

	/*
	 *	Activates this thruster if it thrusts in the desired direction
	 *	@param ThrustDirection - The direction of desired thrust
	 *	@param DeltaTime - time taken to render frame
	 */
	void ActivateThruster(EThrustDirection ThrustDirection, float DeltaTime, bool bIsStabilizing);

	/*
	*	Sets whether of not this thruster is active this frame
	*	@param ThrustDirection - Used to identify if this instruction is relevant to this thruster
	*	@param IsActive - Whether or not this thruster is active this frame
	*/
	void SetThrusterIsActive(EThrustDirection ThrustDirection, bool IsActive);

private:
	
	/*
	 *	Adds force on SpaceshipHull in the given direction
	 *	@param Direction - The direction force will be added in
	 *	@param DeltaTime - time taken to render frame
	 */
	void ThrustInDirection(FVector Direction, float DeltaTime);

	/*
	*	Activates this thruster in order to stabilise the spaceship
	*	@param ThrustDirection - The direction of desired thrust
	*	@param DeltaTime - time taken to render frame
	*/
	void Stabilize(FVector Direction, float DeltaTime);

	UPROPERTY(EditAnywhere)
	EThrusterPositionX ThrusterPositionX;

	UPROPERTY(EditAnywhere)
	EThrusterPositionY ThrusterPositionY;

	UPROPERTY(EditAnywhere)
	EThrusterPositionZ ThrusterPositionZ;

	UPROPERTY(EditAnywhere)
	EThrustDirection ThrustDirection;

	bool bThrusterIsActive = false;
};
