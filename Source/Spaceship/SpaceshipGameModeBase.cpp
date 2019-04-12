// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipGameModeBase.h"

void ASpaceshipGameModeBase::RegisterWithRadarDetectableActors(AActor* Pawn, EFactionEnum Faction, ETargetTypeEnum TargetType)
{
	FRadarActorInformation PawnInfo;
	PawnInfo.SetFaction(Faction);
	PawnInfo.SetTargetType(TargetType);
	RadarDetectableActors.Add(Pawn, PawnInfo);
	//UE_LOG(LogTemp, Warning, TEXT("ASpaceshipGameModeBase::RegisterWithRadarDetectableActors - Registering %s"), *(Pawn->GetName()));
}

void ASpaceshipGameModeBase::DeRegisterFromRadarDetectableActors(AActor * Actor)
{
	RadarDetectableActors.Remove(Actor);
}

TArray<AActor*> ASpaceshipGameModeBase::GetAllRadarDetectableActors()
{
	TArray<AActor *> AllRadarDetectableActors;

	for (const TPair<AActor *, FRadarActorInformation>& pair : RadarDetectableActors)
	{
		AllRadarDetectableActors.Add(pair.Key);
	}

	return AllRadarDetectableActors;
}

TArray<AActor*> ASpaceshipGameModeBase::GetOpposingRadarDetectableActors(EFactionEnum MyFaction)
{
	TArray<AActor *> OpposingRadarDetectableActors;

	for (const TPair<AActor *, FRadarActorInformation>& pair : RadarDetectableActors)
	{
		if (pair.Value.Faction != MyFaction) {
			OpposingRadarDetectableActors.Add(pair.Key);
		}
	}
	return OpposingRadarDetectableActors;
}

TArray<AActor*> ASpaceshipGameModeBase::GetAlliedRadarDetectableActors(EFactionEnum MyFaction)
{
	TArray<AActor *> AlliedRadarDetectableActors;

	for (const TPair<AActor *, FRadarActorInformation>& pair : RadarDetectableActors)
	{
		if (pair.Value.Faction == MyFaction) {
			AlliedRadarDetectableActors.Add(pair.Key);
		}
	}
	return AlliedRadarDetectableActors;
}
