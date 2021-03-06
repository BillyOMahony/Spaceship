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

	HandleThrustInputs(DeltaTime);

	MoveForward(DeltaTime);

	Stabilize(DeltaTime);
	
}

void USpaceshipMovementComponent::HandleThrustInputs(float DeltaTime)
{
	if(ThrustUpPressed)
	{
		for(int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Up, DeltaTime, false);
		}
	}

	if(ThrustDownPressed)
	{
		for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Down, DeltaTime, false);
		}
	}

	if (ThrustLeftPressed)
	{
		for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Left, DeltaTime, false);
		}
	}

	if (ThrustRightPressed)
	{
		for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
		{
			SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Right, DeltaTime, false);
		}
	}
}

void USpaceshipMovementComponent::Pitch(float DeltaTime, float Multiplier)
{
	Multiplier = FMath::Clamp<float>(Multiplier, -1, 1);

	if (SpaceshipHull) {
		FRotator PitchToAdd = FRotator(DeltaTime * PitchPerSec * Multiplier, 0, 0);
		SpaceshipHull->AddLocalRotation(PitchToAdd);
	}
}

void USpaceshipMovementComponent::Yaw(float DeltaTime, float Multiplier)
{
	Multiplier = FMath::Clamp<float>(Multiplier, -1, 1);

	if(SpaceshipHull)
	{
		FRotator YawToAdd = FRotator(0, DeltaTime * YawPerSec * Multiplier, 0);
		SpaceshipHull->AddLocalRotation(YawToAdd);
	}
}

void USpaceshipMovementComponent::Roll(float DeltaTime, float Multiplier)
{
	Multiplier = FMath::Clamp<float>(Multiplier, -1, 1);

	if (SpaceshipHull)
	{
		FRotator RollToAdd = FRotator(0, 0, DeltaTime * RollPerSec * Multiplier);
		SpaceshipHull->AddLocalRotation(RollToAdd);
	}
}

float USpaceshipMovementComponent::GetMainThrottle()
{
	return MainThrottle;
}

float USpaceshipMovementComponent::GetForwardVelocity()
{
	FVector OutDir;
	float OutVel;

	SpaceshipHull->GetComponentVelocity().ToDirectionAndLength(OutDir, OutVel);

	return OutVel * OutDir.X;
}

void USpaceshipMovementComponent::CappedRoll(float DeltaTime, float RollPosition)
{
	// TODO Implement
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

void USpaceshipMovementComponent::Stabilize(float DeltaTime)
{
	// Stabilize in Left/Right Direction
	if (!ThrustLeftPressed && !ThrustRightPressed)
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
			// Activate all thrusters which thrust left
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Left, DeltaTime, true);
			}
			// Deactivate all thrusters which thrust right
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->SetThrusterIsActive(EThrustDirection::Right, false);
			}
		}
		else if(RightVelocity < 0)
		{
			// Activate all thrusters which thrust right
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Right, DeltaTime, true);
			}
			// Deactivate all thrusters which thrust left
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->SetThrusterIsActive(EThrustDirection::Left, false);
			}
		}
	}

	// Stabilize in Up/Down Direction
	if(!ThrustDownPressed && !ThrustUpPressed)
	{
		FVector HullVelocity = SpaceshipHull->GetComponentVelocity();
		FVector OutDir;
		float OutVelocity;
		HullVelocity.ToDirectionAndLength(OutDir, OutVelocity);

		FVector Direction = SpaceshipHull->GetUpVector();
		Direction.Normalize();

		const float UpVector = FVector::DotProduct(Direction, OutVelocity * OutDir);

		if (UpVector > 0)
		{
			// Activate all thrusters which thrust down
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Down, DeltaTime, true);
			}
			// Deactivate all thrusters which thrust up
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->SetThrusterIsActive(EThrustDirection::Up, false);
			}
		}
		else if (UpVector < 0)
		{
			// Activate all thrusters which thrust up
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->ActivateThruster(EThrustDirection::Up, DeltaTime, true);
			}
			// Deactivate all thrusters which thrust down
			for (int32 i = 0; i < SecondaryThrusters.Num(); i++)
			{
				SecondaryThrusters[i]->SetThrusterIsActive(EThrustDirection::Down, false);
			}
		}
	}
}

void USpaceshipMovementComponent::ThrottleUp(float DeltaTime, float Multiplier)
{
	float MainThrottleToAdd = DeltaTime * MainThrottleChangeMultiplier * Multiplier;
	AddMainThrottle(MainThrottleToAdd);
}

void USpaceshipMovementComponent::ThrottleDown(float DeltaTime, float Multiplier)
{
	float MainThrottleToAdd = DeltaTime * MainThrottleChangeMultiplier * -Multiplier;
	AddMainThrottle(MainThrottleToAdd);
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

