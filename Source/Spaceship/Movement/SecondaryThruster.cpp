// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondaryThruster.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


void USecondaryThruster::BeginPlay() {
	Super::BeginPlay();

}

void USecondaryThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (ParticleSystem && bThrusterIsActive)
	{
		ParticleSystem->ActivateSystem();
	}
	else {
		ParticleSystem->DeactivateSystem();
	}
}

void USecondaryThruster::SetThrottle(float Throttle)
{
	this->Throttle = Throttle;
}

void USecondaryThruster::ActivateThruster(EThrustDirection ThrustDirection, float DeltaTime, bool bIsStabilizing)
{
	if (!SpaceshipHull) {
		UE_LOG(LogTemp, Error, TEXT("USecondaryThruster::ActivateThruster - SpaceshipHull not assigned"));
		return;
	}

	if (this->ThrustDirection == ThrustDirection) {
		FVector Direction;

		bThrusterIsActive = true;

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

		if (!bIsStabilizing) {
			ThrustInDirection(Direction, DeltaTime);
		}
		else
		{
			Stabilize(Direction, DeltaTime);
		}
	}
}

void USecondaryThruster::SetThrusterIsActive(EThrustDirection ThrustDirection, bool IsActive)
{
	if (this->ThrustDirection == ThrustDirection) bThrusterIsActive = IsActive;
}

void USecondaryThruster::Stabilize(FVector Direction, float DeltaTime)
{
	
	FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
	FVector OutDir;
	float OutVelocity;
	HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

	Direction.Normalize();

	float DesiredDirectionVelocity = FVector::DotProduct(Direction, OutVelocity * OutDir);

	float SpeedBasedMultiplier = (DesiredDirectionVelocity *-1) / MaxVelocity;

	FVector ForceToAdd = Direction * AccelerationForce * DeltaTime * SpeedBasedMultiplier * DecelerationMultiplier;

	FString ForceBeingAdded = ForceToAdd.ToString();

	float Length = ForceToAdd.Size();

	if (Length < AccelerationForce / 5000.f)
	{
		bThrusterIsActive = false;
	}

	if (Length <  AccelerationForce / 5000000.f)
	{
		return;
	}

	SpaceshipHull->AddForce(ForceToAdd);
}

void USecondaryThruster::ThrustInDirection(FVector Direction, float DeltaTime)
{
	FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
	FVector OutDir;
	float OutVelocity;
	HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

	Direction.Normalize();
	
	float DesiredDirectionVelocity = FVector::DotProduct(Direction, OutVelocity * OutDir);

	if (DesiredDirectionVelocity < MaxVelocity) {
		FVector ForceToAdd = Direction * AccelerationForce * DeltaTime;
		SpaceshipHull->AddForce(ForceToAdd);
	}
}
