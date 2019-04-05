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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire();

	void AttachAmmoCartridge(class AAmmoActor * AmmoCartridge);

	void DetachAmmoCartridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 *	Sets bCanFire to true
	 */
	void AllowFire();

	UPROPERTY(VisibleAnywhere)
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * AmmoAttachmentPointCollider;

	UPROPERTY(EditAnywhere)
	float RateOfFire = 0.5f;

	UPROPERTY(EditAnywhere)
	bool bRequiresAmmo = true;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent * AudioComponent;

	AAmmoActor * AmmoActor;

	bool bCanFire = true;
};
