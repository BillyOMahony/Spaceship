// Fill out your copyright notice in the Description page of Project Settings.

#include "MainThruster.h"
#include "Components/StaticMeshComponent.h"

void UMainThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	AccelerateSpaceship(DeltaTime);
}

void UMainThruster::AddThrottle(float ThrottleToAdd)
{
	Throttle += ThrottleToAdd;
	if(Throttle > 1)
	{
		Throttle = 1;
	}else if(Throttle < 0)
	{
		Throttle = 0;
	}
}

void UMainThruster::AccelerateSpaceship(float DeltaTime)
{
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
	
}
