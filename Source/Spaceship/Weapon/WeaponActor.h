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
	 *	TODO
	 */
	void AimAt(FVector Location);

	/*
	 *	Fires this weapons projectile if possible
	 */
	void Fire();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Turret;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Barrel;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;
};
