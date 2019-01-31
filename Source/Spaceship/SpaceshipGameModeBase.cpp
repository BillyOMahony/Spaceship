// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipGameModeBase.h"

void ASpaceshipGameModeBase::RegisterWithRadarDetectablePawns(APawn* Pawn)
{
	RadarDetectablePawns.Add(Pawn);
}

void ASpaceshipGameModeBase::DeRegisterFromRadarDetectablePawns(APawn* Pawn)
{
	RadarDetectablePawns.Remove(Pawn);
}

TArray<APawn*> ASpaceshipGameModeBase::GetRadarDetectablePawns()
{

	for(int32 i = 0; i < RadarDetectablePawns.Num(); i++)
	{
		FString Name = RadarDetectablePawns[i]->GetName();
	}

	return RadarDetectablePawns;
}


