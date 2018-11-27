// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileWeaponActor.h"
#include "Engine/World.h"
#include "Projectile.h"

void AProjectileWeaponActor::Fire()
{
	if (Projectile)
	{
		FVector SpawnLocation = MunitionSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = MunitionSpawnPoint->GetComponentRotation();
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor(Projectile, &SpawnLocation, &SpawnRotation, SpawnParams);
	}
}
