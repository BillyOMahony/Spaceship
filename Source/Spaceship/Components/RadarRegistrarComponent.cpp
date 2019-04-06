// Fill out your copyright notice in the Description page of Project Settings.

#include "RadarRegistrarComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
URadarRegistrarComponent::URadarRegistrarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URadarRegistrarComponent::BeginPlay()
{
	Super::BeginPlay();

	RegisterPawn();
	
}


// Called every frame
void URadarRegistrarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EFactionEnum URadarRegistrarComponent::GetFaction()
{
	return Faction;
}

ETargetTypeEnum URadarRegistrarComponent::GetTargetType()
{
	return TargetType;
}

void URadarRegistrarComponent::RegisterPawn()
{
	// Register Pawn with GameMode RadarDetectablePawns
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->RegisterWithRadarDetectableActors(GetOwner(), Faction, TargetType);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASpaceshipPawn::BeginPlay - Cannot find GameMode"));
	}
	// TODO Set Faction in GameMode
}

