// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VRGun.h"
#include "GrenadeLauncher.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API AGrenadeLauncher : public AVRGun
{
	GENERATED_BODY()

	AGrenadeLauncher();

public:
	void Fire() override;

private:
	/*
	 *	Finds the nearest Radar Detectable Pawn which this gun is being aimed towards
	 */
	AActor * FindTargetedActor();

	/*
	 *	@return the angle in degrees ActorToCheck is from the forward vector of the barrel
	 */
	float GetAngleOfActorFromBarrel(AActor * ActorToCheck);

	UPROPERTY(EditAnywhere)
	float HomingAimAngleAcceptance = 10.f;

	AActor * TargetedActor = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHomingGrenadeProjectile> Projectile;

	class URadarComponent * RadarComponent;
};
