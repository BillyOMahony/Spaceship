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
