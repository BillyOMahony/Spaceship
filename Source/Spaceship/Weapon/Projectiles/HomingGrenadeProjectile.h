// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomingGrenadeProjectile.generated.h"

UCLASS()
class SPACESHIP_API AHomingGrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingGrenadeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/*
	 *	Sets variables and activates the movement components of this projectile
	 */
	void LaunchProjectile(class ACharacter * OwningCharacter, AActor * TargetActor);

private:
	/*
	 *	TODO Plays sounds/ particles related to the explosion of this projectile
	 *	TODO Applies damage to nearby actors
	 */
	void ExplodeProjectile();

	/*
	 *	Activates homing for this component
	 */
	void ActivateHoming();

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent * Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	class UParticleSystemComponent * TrailComponent;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	class UAudioComponent * AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Setup")
	USoundBase * MissileLaunchSound;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float BaseDamage = 40.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float MinDamage = 0.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageInnerRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageOuterRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageFalloff = 1.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ProjectileAliveTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "Tracking")
	float DelayedHomingActivationTime = .5f;

	UPROPERTY(EditAnywhere, Category = "Tracking")
	float InitialHomingMagnitude = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Tracking")
	float HomingMagnitudeMultiplierPerSecond = 3.f;

	UPROPERTY(EditAnywhere, Category = "Death")
	TSubclassOf<class AProjectileDeathParticleActor> Explosion;

	class ACharacter * OwnerCharacter;
	
	AActor * TargetActor;

};
