// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipMovementComponent.h"
#include "MainThruster.h"
#include "SecondaryThruster.h"

// Sets default values for this component's properties
USpaceshipMovementComponent::USpaceshipMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpaceshipMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpaceshipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveForward(DeltaTime);
}

void USpaceshipMovementComponent::AddMainThrottle(float ThrottleToAdd)
{
	MainThrottle += ThrottleToAdd;
	if (MainThrottle > 1)
	{
		MainThrottle = 1;
	}
	else if (MainThrottle < 0)
	{
		MainThrottle = 0;
	}
}

void USpaceshipMovementComponent::SetSpaceshipHull(UStaticMeshComponent * SpaceshipHull)
{
	this->SpaceshipHull = SpaceshipHull;

	// Set SpaceshipHull for each Thruster
	for (int32 i = 0; i < MainThrusters.Num(); i++) {
		MainThrusters[i]->GetDefaultObject<UMainThruster>()->SetSpaceshipHull(SpaceshipHull);
	}
}

void USpaceshipMovementComponent::MoveForward(float DeltaTime)
{
	for (int32 i = 0; i < MainThrusters.Num(); i++) {
		MainThrusters[i]->GetDefaultObject<UMainThruster>()->SetThrottle(MainThrottle);
		MainThrusters[i]->GetDefaultObject<UMainThruster>()->AccelerateSpaceship(DeltaTime);
	}
}

void USpaceshipMovementComponent::Stabilise()
{

}


