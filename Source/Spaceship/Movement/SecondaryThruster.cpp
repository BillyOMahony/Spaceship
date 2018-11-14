// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondaryThruster.h"

void USecondaryThruster::BeginPlay() {
	Super::BeginPlay();

}

void USecondaryThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{

}

void USecondaryThruster::SetThrottle(float Throttle)
{
	this->Throttle = Throttle;
}

void USecondaryThruster::ActivateThruster(EThrustDirection ThrustDirection, float DeltaTime)
{
	if (!SpaceshipHull) {
		UE_LOG(LogTemp, Error, TEXT("USecondaryThruster::ActivateThruster - SpaceshipHull not assigned"));
		return;
	}
	if (this->ThrustDirection == ThrustDirection) {
		FVector Direction;

		switch (ThrustDirection) {
		case EThrustDirection::Up:
			Direction = SpaceshipHull->GetUpVector();
			break;

		case EThrustDirection::Down:
			Direction = SpaceshipHull->GetUpVector() * -1;
			break;

		case EThrustDirection::Left:
			Direction = SpaceshipHull->GetRightVector() * -1;
			break;

		case EThrustDirection::Right:
			Direction = SpaceshipHull->GetRightVector();
			break;
		}

		ThrustInDirection(Direction, DeltaTime);
	}
}

void USecondaryThruster::ThrustInDirection(FVector Direction, float DeltaTime)
{
	FVector ForceToAdd = Direction * AccelerationForce * DeltaTime;
	SpaceshipHull->AddForce(ForceToAdd);
	/*
	FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
	FVector OutDir;
	float OutVelocity;
	HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

	FVector ActorForwardVector = SpaceshipHull->GetForwardVector();
	ActorForwardVector.Normalize();

	float ForwardVelocity = FVector::DotProduct(ActorForwardVector, OutVelocity * OutDir);

	UE_LOG(LogTemp, Warning, TEXT("ForwardVelocity: %f"), ForwardVelocity);

	if (ForwardVelocity <= MaxVelocity * Throttle)
	{
		FVector ForceToAdd = ActorForwardVector * AccelerationForce * DeltaTime * Throttle;
		SpaceshipHull->AddForce(ForceToAdd);
	}
	else if (ForwardVelocity > MaxVelocity * Throttle)
	{
		// Calculate a multiplier based on current speed / max speed, this causes spaceship to slow down at a nicer rate
		// At Higher speeds it slows faster than at lower speeds
		float SpeedBasedMultiplier = ForwardVelocity / MaxVelocity;

		FVector ForceToAdd = ActorForwardVector * AccelerationForce * DeltaTime * DecelerationMultiplier * SpeedBasedMultiplier;
		SpaceshipHull->AddForce(-ForceToAdd);
	}
	*/
}
