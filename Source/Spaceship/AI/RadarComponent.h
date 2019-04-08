// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceshipGameModeBase.h"
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

	/*
	 *	@return the DetectedPawns array
	 */
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetDetectedActors() const;

	/*
	 * @return the closest actor in DetectedPawns to the owner actor
	 */
	UFUNCTION(BlueprintCallable)
	AActor* GetClosestActor(ETargetTypeEnum TargetType);

	void SetIgnorePlayer(bool IgnorePlayer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	/*
	 *	Populates the DetectedPawns Array
	 */
	void RadarBurst();

	/*
	 *	Checks if the distance between Actor and the owner of this component is less than RadarRange
	 *	@param Actor - The Actor to check the distance to
	 *	@return whether the actor is within range
	 */
	bool IsActorWithinRange(AActor * Pawn) const;

	/*
	 *	Checks if the pawn can be seen by the radar
	 *	The Pawn cannot be seen if there is an actor between the radar and pawn
	 *	@param Actor - The Actor to check
	 *	@return whether the actor is visible or not
	 */
	bool IsActorRadarVisible(AActor* Actor) const;

	UPROPERTY(EditAnywhere, Category = "Radar")
	bool bRadarEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Radar")
	float RadarRange = 1000000.f;

	UPROPERTY(EditAnywhere, Category = "Radar")
	float RadarBurstRate = 1.f;

	TArray<AActor*> DetectedActors;

	bool bIgnorePlayer = false;

};
