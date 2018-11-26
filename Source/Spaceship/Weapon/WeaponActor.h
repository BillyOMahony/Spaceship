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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 *	Rotates Turret and Barrel so if they fire the projectiles will hit Location
	 *	@param Location - The Vector to aim at
	 */
	void AimAt(FVector Location);

	/*
	 *	Fires this weapons projectile if possible
	 */
	void Fire();

	/*
	 *	@param OwningActor - The Actor that spawned this Actor
	 */
	void SetOwningActor(AActor * OwningActor);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Turret;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Barrel;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;

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

	AActor * OwningActor;

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
