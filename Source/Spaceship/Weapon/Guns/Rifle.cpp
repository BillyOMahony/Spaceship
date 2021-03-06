// Fill out your copyright notice in the Description page of Project Settings.

#include "Rifle.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Weapon/Ammo/AmmoActor.h"
#include "Components/AudioComponent.h"
#include "Weapon/Projectile.h"

void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAutoIsFiring) {
		Fire();
	}
}

void ARifle::OnFire()
{
	bAutoIsFiring = true;
}

void ARifle::OnStopFire()
{
	bAutoIsFiring = false;
}

void ARifle::Fire()
{
	if (Projectile && (AmmoActor || !bRequiresAmmo) && bCanFire) {
		if (!bRequiresAmmo || AmmoActor->GetAmmo() > 0 ) {
			FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
			FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
			FActorSpawnParameters SpawnParams;

			auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation);
			SpawnedProjectile->LaunchProjectile(InitialProjectileSpeed);

			if (AudioComponent->Sound)AudioComponent->Play();

			if (AmmoActor) {
				AmmoActor->FireRound();
			}

			bCanFire = false;
			FTimerHandle RateOfFireTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				RateOfFireTimerHandle,
				this,
				&ARifle::AllowFire,
				RateOfFire,
				false
			);
		}
	}
}
