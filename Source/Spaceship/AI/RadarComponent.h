// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RadarComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API URadarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadarComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TArray<APawn*> GetDetectedPawns();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	/*
	 *	Populates the DetectedPawns Array
	 */
	void RadarBurst();

	/*
	 *	Checks if the distance between Pawn and the owner of this component is less than RadarRange
	 *	@param Pawn - The Pawn to check the distance to
	 *	@return whether the pawn is within range
	 */
	bool IsPawnWithinRange(APawn * Pawn);

	/*
	 *	Checks if the pawn can be seen by the radar
	 *	The Pawn cannot be seen if there is an actor between the radar and pawn
	 *	@param Pawn - The Pawn to check
	 *	@return whether the pawn is visible or not
	 */
	bool IsPawnRadarVisible(APawn * Pawn);

	UPROPERTY(EditAnywhere, Category = "Radar")
	bool bRadarEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Radar")
	float RadarRange = 10000.f;

	UPROPERTY(EditAnywhere, Category = "Radar")
	float RadarBurstRate = 1.f;

	TArray<APawn*> DetectedPawns;
};
