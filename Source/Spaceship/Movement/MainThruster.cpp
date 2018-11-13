// Fill out your copyright notice in the Description page of Project Settings.

#include "MainThruster.h"
#include "Components/StaticMeshComponent.h"

// Called when the game starts
void UMainThruster::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UMainThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	AccelerateSpaceship(DeltaTime);
}

void UMainThruster::SetSpaceshipHull(UStaticMeshComponent * Hull)
{
	SpaceshipHull = Hull;
}

void UMainThruster::AccelerateSpaceship(float DeltaTime)
{
	if (InvertAcceleration)
	{
		DeltaTime *= -1;
	}

	FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
	FVector OutDir;
	float OutVelocity;
	HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

	UE_LOG(LogTemp, Warning, TEXT("Velocity: %f"), OutVelocity);

	if(OutVelocity < MaxVelocity)
	{
		SpaceshipHull->AddForce(FVector(AccelerationForce * DeltaTime, 0, 0));
	}
	
}
