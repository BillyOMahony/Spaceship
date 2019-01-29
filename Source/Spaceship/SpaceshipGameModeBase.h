// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceshipGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API ASpaceshipGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/*
	 *	@param Pawn - the Pawn being added to RadarDetectablePawns
	 */
	void RegisterWithRadarDetectablePawns(APawn* Pawn);

	/*
	 *	@param Pawn - the Pawn being removed from Radar DetectablePawns
	 */
	void DeRegisterFromRadarDetectablePawns(APawn * Pawn);

	/*
	 *  @return The RadarDetectablePawns array
	 */
	TArray<APawn *> GetRadarDetectablePawns();

private:
	TArray<APawn *> RadarDetectablePawns;

};
