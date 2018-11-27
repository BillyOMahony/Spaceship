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
	virtual void Fire() override;

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;
};
