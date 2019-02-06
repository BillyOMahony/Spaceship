// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceshipGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EFactionEnum : uint8
{
	FE_Good	UMETA(DisplayName = "Good Guys"),
	FE_Bad	UMETA(DisplayName = "Bad Guys")
};

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
	void RegisterWithRadarDetectablePawns(APawn* Pawn, EFactionEnum Faction);

	/*
	 *	@param Pawn - the Pawn being removed from Radar DetectablePawns
	 */
	void DeRegisterFromRadarDetectablePawns(APawn * Pawn);

	/*
	 *  @return The RadarDetectablePawns array
	 */
	TArray<APawn *> GetAllRadarDetectablePawns();

	/*
	 *  @return RadarDetectablePawns in opposing Factions
	 */
	TArray<APawn *> GetOpposingRadarDetectablePawns(EFactionEnum MyFaction);

private:
	TMap<APawn *, EFactionEnum> RadarDetectablePawns;


};
