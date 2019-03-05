// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickupable/VRPickupableActor.h"
#include "VRGun.generated.h"

UCLASS()
class SPACESHIP_API AVRGun : public AVRPickupableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	void PickUp(ACharacter * Character);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	float HomingAimAngleAcceptance = 10.f;

	AActor * TargetedActor = nullptr;

	/*
	 *	The class of projectile which will be spawned
	*/
	UPROPERTY(EditAnywhere)
	//TSubclassOf<class AProjectile> Projectile;
	TSubclassOf<class AHomingGrenadeProjectile> Projectile;

	class URadarComponent * RadarComponent;

	/*
	 *	Finds the nearest Radar Detectable Pawn which this gun is being aimed towards
	 */
	AActor * FindTargetedActor();

	float GetAngleOfActorFromBarrel(AActor * ActorToCheck);

};
