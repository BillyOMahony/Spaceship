// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileWeaponActor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"

void AProjectileWeaponActor::FireIfOnTarget(AActor * Target)
{
	if (Target) {
		if (GetAngleToTarget(Target) < AimAcceptanceAngle) {
			Fire();
		}
	}
}

void AProjectileWeaponActor::AimAtActor(AActor * Actor)
{
	if (!ensure(Turret && Barrel)) return;

	float DistanceToActor = (Actor->GetActorLocation() - MunitionSpawnPoint->GetComponentLocation()).Size();
	float Time = DistanceToActor / InitialProjectileSpeed;
	FVector PredictedPosition = Actor->GetActorLocation() + (Actor->GetVelocity() * Time);

	FTransform BarrelTipTransform = MunitionSpawnPoint->GetComponentTransform();
	FVector AimDirection = BarrelTipTransform.InverseTransformPosition(PredictedPosition).GetSafeNormal();

	auto DeltaRotator = AimDirection.Rotation();

	RotateBarrel(DeltaRotator.Pitch);

	if (DeltaRotator.Yaw > 180 || DeltaRotator.Yaw < -180)
	{
		RotateTurret(-DeltaRotator.Yaw);
	}
	else
	{
		RotateTurret(DeltaRotator.Yaw);
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
		if (SpawnedProjectile) {
			SpawnedProjectile->LaunchProjectile(InitialProjectileSpeed);
		}
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
	else MuzzleFlash->Deactivate();
}
