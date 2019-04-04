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

	void AttachAmmoCartridge(class AAmmoActor * AmmoCartridge);

	void DetachAmmoCartridge();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * AmmoAttachmentPointCollider;

	UPROPERTY(EditAnywhere)
	float HomingAimAngleAcceptance = 10.f;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent * AudioComponent;

	AActor * TargetedActor = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHomingGrenadeProjectile> Projectile;

	class URadarComponent * RadarComponent;

	AAmmoActor * AmmoActor;

	/*
	 *	Finds the nearest Radar Detectable Pawn which this gun is being aimed towards
	 */
	AActor * FindTargetedActor();

	/*
	 *	@return the angle in degrees ActorToCheck is from the forward vector of the barrel
	 */
	float GetAngleOfActorFromBarrel(AActor * ActorToCheck);

};
