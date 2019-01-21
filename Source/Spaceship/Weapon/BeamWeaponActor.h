// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "BeamWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API ABeamWeaponActor : public AWeaponActor
{
	GENERATED_BODY()

public:
	ABeamWeaponActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void FireIfOnTarget(AActor* Target) override;

protected:

private:
	/*
	*	Fires a projectile if possible
	*/
	void Fire();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * LaserMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Beam")
	float DamagePerSecond = 30.f;

	UPROPERTY(EditAnywhere, Category = "Beam")
	float BeamMaxLength = 100000.f;

	float DeltaTime;

};
