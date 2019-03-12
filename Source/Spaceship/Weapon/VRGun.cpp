// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGun.h"
#include "Engine/World.h"
#include "Weapon/Projectiles/HomingGrenadeProjectile.h"
#include "Weapon/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "AI/RadarComponent.h"

// Sets default values
AVRGun::AVRGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("Projectile Spawn Point"));
	ProjectileSpawnPoint->AttachToComponent(PickupableMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileSpawnPoint->SetupAttachment(PickupableMesh);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	AudioComponent->AttachToComponent(ProjectileSpawnPoint, FAttachmentTransformRules::KeepRelativeTransform);
	AudioComponent->SetupAttachment(ProjectileSpawnPoint);
	AudioComponent->SetAutoActivate(false);

	RadarComponent = CreateDefaultSubobject<URadarComponent>(FName("Radar Component"));
	RadarComponent->SetIgnorePlayer(true);
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

		auto SpawnedProjectile = GetWorld()->SpawnActor<AHomingGrenadeProjectile>(Projectile, SpawnLocation, SpawnRotation);
		SpawnedProjectile->LaunchProjectile(nullptr, FindTargetedActor());

		if(AudioComponent->Sound)AudioComponent->Play();
	}
}

void AVRGun::PickUp(ACharacter * Character)
{
	
}

AActor * AVRGun::FindTargetedActor()
{
	auto DetectedPawns = RadarComponent->GetDetectedPawns();

	if (DetectedPawns.Num() > 0) {
		AActor * ClosestActor = DetectedPawns[0];
		float ClosestActorDistance = (ClosestActor->GetActorLocation() - GetActorLocation()).Size();
		//GetAngleOfActorFromBarrel(DetectedPawns[0]);

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

float AVRGun::GetAngleOfActorFromBarrel(AActor * ActorToCheck)
{
	FVector GunAimVector = ProjectileSpawnPoint->GetForwardVector();

	FVector ActorVectorFromGun = (ActorToCheck->GetActorLocation() - ProjectileSpawnPoint->GetComponentLocation()).GetSafeNormal();

	float DotProduct = FVector::DotProduct(ActorVectorFromGun, GunAimVector);

	float RadiansAngle = acosf(DotProduct);

	return FMath::RadiansToDegrees(RadiansAngle);
}

