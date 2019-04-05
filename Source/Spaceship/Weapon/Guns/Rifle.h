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
	void Fire() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;
};
