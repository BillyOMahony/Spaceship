// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipMovementComponent.h"
#include "Components/StaticMeshComponent.h"
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

	PopulateMainThrusters();
	PopulateSecondaryThrusters();
	
}

// Called every frame
void USpaceshipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleThrottle(DeltaTime);

	HandleThrustInputs(DeltaTime);

	MoveForward(DeltaTime);

	//Stabilise(DeltaTime);
}

void USpaceshipMovementComponent::HandleThrustInputs(float DeltaTime)
{
	if(ThrustUpPressed)
	{
		for(int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Up, DeltaTime);
		}
	}

	if(ThrustDownPressed)
	{
		for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Down, DeltaTime);
		}
	}

	if (ThrustLeftPressed)
	{
		for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Left, DeltaTime);
		}
	}

	if (ThrustRightPressed)
	{
		for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Right, DeltaTime);
		}
	}
}

void USpaceshipMovementComponent::HandleThrottle(float DeltaTime)
{
	if (ThrottleUpPressed) {
		float MainThrottleToAdd = DeltaTime * MainThrottleChangeMultiplier;
		AddMainThrottle(MainThrottleToAdd);
	}
	else if (ThrottleDownPressed) {
		float MainThrottleToAdd = DeltaTime * MainThrottleChangeMultiplier * -1;
		AddMainThrottle(MainThrottleToAdd);
	}
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
		MainThrusters[i]->SetSpaceshipHull(SpaceshipHull);
	}
	for(int32 i = 0; i < SecondaryThrusters.Num(); i++)
	{
		SecondaryThrusters[i]->SetSpaceshipHull(SpaceshipHull);
	}
}

void USpaceshipMovementComponent::PopulateMainThrusters()
{
	GetOwner()->GetComponents<UMainThruster>(MainThrusters);
}

void USpaceshipMovementComponent::PopulateSecondaryThrusters()
{
	GetOwner()->GetComponents<USecondaryThruster>(SecondaryThrusters);
}

void USpaceshipMovementComponent::MoveForward(float DeltaTime)
{
	for (int32 i = 0; i < MainThrusters.Num(); i++) {
		MainThrusters[i]->SetThrottle(MainThrottle);
	}
}

void USpaceshipMovementComponent::Stabilise(float DeltaTime)
{
	// Stabilise in Left/Right Direction
	if (!ThrustDownPressed && !ThrustUpPressed)
	{
		FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
		FVector OutDir;
		float OutVelocity;
		HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

		FVector Direction = SpaceshipHull->GetRightVector();
		Direction.Normalize();

		float RightVelocity = FVector::DotProduct(Direction, OutVelocity * OutDir);

		if(RightVelocity > 0)
		{
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Left, DeltaTime);
			}
		}
		else if(RightVelocity < 0)
		{
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Right, DeltaTime);
			}
		}
	}

	// Stabilise in Up/Down Direction
	if(!ThrustLeftPressed && !ThrustRightPressed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Donkey"));

		FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
		FVector OutDir;
		float OutVelocity;
		HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

		FVector Direction = SpaceshipHull->GetUpVector();
		Direction.Normalize();

		float UpVector = FVector::DotProduct(Direction, OutVelocity * OutDir);

		if (UpVector > 0)
		{
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Down, DeltaTime);
			}
		}
		else if (UpVector < 0)
		{
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Up, DeltaTime);
			}
		}
	}
}

void USpaceshipMovementComponent::SetThrottleUpPressed(bool ThrottleUpPressed)
{
	this->ThrottleUpPressed = ThrottleUpPressed;
}

void USpaceshipMovementComponent::SetThrottleDownPressed(bool ThrottleDownPressed)
{
	this->ThrottleDownPressed = ThrottleDownPressed;
}

void USpaceshipMovementComponent::SetThrustUpPressed(bool ThrustUpPressed)
{
	this->ThrustUpPressed = ThrustUpPressed;
}

void USpaceshipMovementComponent::SetThrustDownPressed(bool ThrustDownPressed)
{
	this->ThrustDownPressed = ThrustDownPressed;
}

void USpaceshipMovementComponent::SetThrustLeftPressed(bool ThrustLeftPressed)
{
	this->ThrustLeftPressed = ThrustLeftPressed;
}

void USpaceshipMovementComponent::SetThrustRightPressed(bool ThrustRightPressed)
{
	this->ThrustRightPressed = ThrustRightPressed;
}

