// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGun.h"
#include "Engine/World.h"
#include "Weapon/Projectiles/HomingGrenadeProjectile.h"
#include "Weapon/Projectile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVRGun::AVRGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("Projectile Spawn Point"));
	ProjectileSpawnPoint->AttachToComponent(PickupableMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileSpawnPoint->SetupAttachment(PickupableMesh);
}

// Called when the game starts or when spawned
void AVRGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVRGun::Fire()
{
	if (Projectile) {
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		FActorSpawnParameters SpawnParams;

		UE_LOG(LogTemp, Error, TEXT("C++: Loc: %s, Rot: %s"), *(SpawnLocation.ToString()), *(SpawnRotation.ToString()));

		auto SpawnedProjectile = GetWorld()->SpawnActor<AHomingGrenadeProjectile>(Projectile, SpawnLocation, SpawnRotation);
		SpawnedProjectile->LaunchProjectile(nullptr, nullptr);
	}
}

void AVRGun::PickUp(UActorComponent * Component)
{
	
}

