// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileWeaponActor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"

void AProjectileWeaponActor::FireIfOnTarget(AActor * Target)
{
	// Raycast
	FHitResult HitResult;

	bool HitFound = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		MunitionSpawnPoint->GetComponentLocation(),
		MunitionSpawnPoint->GetComponentLocation() + (MunitionSpawnPoint->GetForwardVector() * TraceRange),
		ECollisionChannel::ECC_Camera
	);

	if(HitResult.GetActor())
	{
		if(HitResult.GetActor() == Target)
		{
			Fire();
		}
	}
}

void AProjectileWeaponActor::Fire()
{
	if(bCanFireProjectile && Projectile)
	{
		if(MuzzleFlash)
		{
			MuzzleFlash->Activate();
		}

		// Angle offset to reduce accuracy
		float PitchOffset = FMath::RandRange(-AngleOffset, AngleOffset);
		float YawOffset = FMath::RandRange(-AngleOffset, AngleOffset);

		FRotator AngleOffset = FRotator(PitchOffset, YawOffset, 0);

		FVector SpawnLocation = MunitionSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = MunitionSpawnPoint->GetComponentRotation();
		SpawnRotation += AngleOffset;
		FActorSpawnParameters SpawnParams;
		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation);
		SpawnedProjectile->LaunchProjectile();
		bCanFireProjectile = false;
		GetWorld()->GetTimerManager().SetTimer(
			RateOfFireTimerHandle,
			this, 
			&AProjectileWeaponActor::AllowFiringOfProjectile, 
			1.f / RateOfFire, 
			false
		);
	}
}

void AProjectileWeaponActor::AllowFiringOfProjectile()
{
	bCanFireProjectile = true;
}

void AProjectileWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAttemptingToFire) Fire();
}
