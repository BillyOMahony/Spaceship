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

UENUM(BlueprintType)
enum class ETargetTypeEnum : uint8
{
	TT_Aerial UMETA(DisplayName = "Aerial"),
	TT_Ground UMETA(DisplayName = "Ground")
};

UENUM(BlueprintType)
enum class EOperationEnum : uint8
{
	OE_GreaterThan	UMETA(DisplayName = "Greater Than"),
	OE_LessThan		UMETA(DisplayName = "Less Than")
};

USTRUCT()
struct FRadarActorInformation
{
	GENERATED_BODY()

	ETargetTypeEnum TargetType;

	ETargetTypeEnum GetTargetType() {
		return TargetType;
	}

	void SetTargetType(ETargetTypeEnum TargetType) {
		this->TargetType = TargetType;
	}

	EFactionEnum Faction;

	EFactionEnum GetFaction() {
		return Faction;
	}

	void SetFaction(EFactionEnum Faction) {
		this->Faction = Faction;
	}

	FRadarActorInformation()
	{
	}
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
	UFUNCTION(BlueprintCallable)
	void RegisterWithRadarDetectableActors(AActor* Actor, EFactionEnum Faction, ETargetTypeEnum TargetType);

	/*
	 *	@param Pawn - the Pawn being removed from Radar DetectablePawns
	 */
	UFUNCTION(BlueprintCallable)
	void DeRegisterFromRadarDetectableActors(AActor * Actor);

	/*
	 *  @return The RadarDetectablePawns array
	 */
	TArray<AActor *> GetAllRadarDetectableActors();

	/*
	 *  @return RadarDetectablePawns in opposing Factions
	 */
	TArray<AActor *> GetOpposingRadarDetectableActors(EFactionEnum MyFaction);

private:
	TMap<AActor *, FRadarActorInformation> RadarDetectableActors;


};
