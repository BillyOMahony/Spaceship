// Fill out your copyright notice in the Description page of Project Settings.

#include "RadarComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
URadarComponent::URadarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void URadarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void URadarComponent::RadarBurst()
{

}


// Called every frame
void URadarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// Get Singleton List (GameMode)

	// Raycast towards each Pawn ( get normalised vector to pawn as angle)

	// Get First hit and check if pawn


}

