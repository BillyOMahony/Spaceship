// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipWeaponsComponent.h"
#include "HardpointComponent.h"

// Sets default values for this component's properties
USpaceshipWeaponsComponent::USpaceshipWeaponsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpaceshipWeaponsComponent::BeginPlay()
{
	Super::BeginPlay();

	// Populate Hardpoint Array
	GetOwner()->GetComponents<UHardpointComponent>(Hardpoints);

	for (int32 i = 0; i < Hardpoints.Num(); i++)
	{
		Hardpoints[i]->SpawnWeapon();
	}
	
}


// Called every frame
void USpaceshipWeaponsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpaceshipWeaponsComponent::AimAt(FVector Location)
{
	for (int32 i = 0; i < Hardpoints.Num(); i++)
	{
		Hardpoints[i]->AimWeaponAt(Location);
	}
}

void USpaceshipWeaponsComponent::BeginFireWeapons()
{
	for (int32 i = 0; i < Hardpoints.Num(); i++)
	{
		Hardpoints[i]->BeginFireWeapon();
	}
}

void USpaceshipWeaponsComponent::EndFireWeapons()
{
	for (int32 i = 0; i < Hardpoints.Num(); i++)
	{
		Hardpoints[i]->EndFireWeapon();
	}
}

void USpaceshipWeaponsComponent::FireIfOnTarget(AActor * Target)
{
	for (int32 i = 0; i < Hardpoints.Num(); i++)
	{
		Hardpoints[i]->FireIfOnTarget(Target);
	}
}

