// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipGameModeBase.h"

void ASpaceshipGameModeBase::RegisterWithRadarDetectablePawns(APawn* Pawn, EFactionEnum Faction)
{
	RadarDetectablePawns.Add(Pawn, Faction);
}

void ASpaceshipGameModeBase::DeRegisterFromRadarDetectablePawns(APawn* Pawn)
{
	RadarDetectablePawns.Remove(Pawn);
}

TArray<APawn*> ASpaceshipGameModeBase::GetAllRadarDetectablePawns()
{
	TArray<APawn *> AllRadarDetectablePawns;

	for (const TPair<APawn *, EFactionEnum>& pair : RadarDetectablePawns)
	{
		AllRadarDetectablePawns.Add(pair.Key);
	}

	return AllRadarDetectablePawns;
}

TArray<APawn*> ASpaceshipGameModeBase::GetOpposingRadarDetectablePawns(EFactionEnum MyFaction)
{
	TArray<APawn *> OpposingRadarDetectablePawns;

	for (const TPair<APawn *, EFactionEnum>& pair : RadarDetectablePawns)
	{
		if (pair.Value != MyFaction) {
			OpposingRadarDetectablePawns.Add(pair.Key);
		}
	}

	return OpposingRadarDetectablePawns;
}
