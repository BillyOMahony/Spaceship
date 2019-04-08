// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VRGun.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API ARifle : public AVRGun
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void OnFire() override;

	void OnStopFire() override;

protected:
	void Fire() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere)
	float InitialProjectileSpeed = 100000.f;
};
