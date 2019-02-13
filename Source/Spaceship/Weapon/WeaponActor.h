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

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent * MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere)
	float TraceRange = 50000.f;

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

	/*
	 *	This method if for use with AI
	 *	Fires only if aiming at Target
	 *	@param Target - The actor to check if aimed at
	 */
	virtual void FireIfOnTarget(AActor* Target);

	/*
	 *	Sets the Target Actor
	 */
	void SetTargetActor(AActor * TargetActor);

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

	AActor * TargetActor = nullptr;

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
