// Fill out your copyright notice in the Description page of Project Settings.

#include "GrenadeLauncher.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Weapon/Projectiles/HomingGrenadeProjectile.h"
#include "Weapon/Ammo/AmmoActor.h"
#include "Components/AudioComponent.h"
#include "AI/RadarComponent.h"

AGrenadeLauncher::AGrenadeLauncher() 
{
	RadarComponent = CreateDefaultSubobject<URadarComponent>(FName("Radar Component"));
	RadarComponent->SetIgnorePlayer(true);
}

void AGrenadeLauncher::Fire()
{
	if (Projectile && AmmoActor && bCanFire) {
		if (AmmoActor->GetAmmo() > 0 || !bRequiresAmmo) {
			FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
			FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
			FActorSpawnParameters SpawnParams;

			auto SpawnedProjectile = GetWorld()->SpawnActor<AHomingGrenadeProjectile>(Projectile, SpawnLocation, SpawnRotation);
			SpawnedProjectile->LaunchProjectile(nullptr, FindTargetedActor());

			if (AudioComponent->Sound)AudioComponent->Play();

			AmmoActor->FireRound();

			bCanFire = false;
			FTimerHandle RateOfFireTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				RateOfFireTimerHandle,
				this,
				&AGrenadeLauncher::AllowFire,
				RateOfFire,
				false
			);
		}
	}
}

AActor * AGrenadeLauncher::FindTargetedActor()
{
	auto DetectedPawns = RadarComponent->GetDetectedPawns();

	if (DetectedPawns.Num() > 0) {
		AActor * ClosestActor = DetectedPawns[0];
		float ClosestActorDistance = (ClosestActor->GetActorLocation() - GetActorLocation()).Size();

		for (int32 i = 1; i < DetectedPawns.Num(); i++) {
			if (GetAngleOfActorFromBarrel(DetectedPawns[i]) < HomingAimAngleAcceptance) {
				float NewActorDistance = (DetectedPawns[i]->GetActorLocation() - GetActorLocation()).Size();

				if (NewActorDistance < ClosestActorDistance) {
					ClosestActor = DetectedPawns[i];
					ClosestActorDistance = NewActorDistance;
				}
			}
		}

		if (GetAngleOfActorFromBarrel(ClosestActor) < HomingAimAngleAcceptance) {
			return ClosestActor;
		}
	}

	return nullptr;
}

float AGrenadeLauncher::GetAngleOfActorFromBarrel(AActor * ActorToCheck)
{
	FVector GunAimVector = ProjectileSpawnPoint->GetForwardVector();

	FVector ActorVectorFromGun = (ActorToCheck->GetActorLocation() - ProjectileSpawnPoint->GetComponentLocation()).GetSafeNormal();

	float DotProduct = FVector::DotProduct(ActorVectorFromGun, GunAimVector);

	float RadiansAngle = acosf(DotProduct);

	return FMath::RadiansToDegrees(RadiansAngle);
}
