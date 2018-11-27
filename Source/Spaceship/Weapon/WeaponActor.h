// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class SPACESHIP_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent * MunitionSpawnPoint;

	bool bAttemptingToFire = false;

public:	

	/*
	 *	Rotates Turret and Barrel so if they fire the projectiles will hit Location
	 *	@param Location - The Vector to aim at
	 */
	void AimAt(FVector Location);

	/*
	 *	Sets this weapon to automatically fire when possible
	 */
	void BeginFireWeapon();

	/*
	 *	Stops this weapon from firing
	 */
	void EndFireWeapon();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Turret;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Barrel;

	UPROPERTY(EditAnywhere)
	float MaxTurretDegPerSec = 90;

	UPROPERTY(EditAnywhere)
	float MaxTurretSwivel = 30;

	UPROPERTY(EditAnywhere)
	float MaxBarrelDegPerSec = 90;

	UPROPERTY(EditAnywhere)
	float MaxBarrelElevation = 60;

	UPROPERTY(EditAnywhere)
	float MinBarrelElevation = -30;

	/*
	 *	Rotates the turret
	 *	@param RelativeSpeed - Decides the direction of rotation
	 */
	void RotateTurret(float RelativeSpeed);

	/*
	 *	Rotates the barrel
	 *	@param RelativeSpeed - Decides the direction of rotation
	 */
	void RotateBarrel(float RelativeSpeed);
};
