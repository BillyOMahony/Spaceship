// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "ProjectileWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API AProjectileWeaponActor : public AWeaponActor
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

private:
	/*
	*	Fires a projectile if possible
	*/
	void Fire();

	/*
	 *	Sets bCanFireProjectile to true
	 */
	void AllowFiringOfProjectile();

	/*
	 *	The class of projectile which will be spawned
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;

	/*
	 *	Number of projectiles which will fire per second
	 */
	UPROPERTY(EditAnywhere)
	float RateOfFire = 20.f;

	bool bCanFireProjectile = true;

	FTimerHandle RateOfFireTimerHandle;
};
