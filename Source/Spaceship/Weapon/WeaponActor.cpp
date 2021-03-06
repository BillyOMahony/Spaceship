// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(FName("Turret"));
	SetRootComponent(Turret);

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Barrel"));
	Barrel->AttachToComponent(Turret, FAttachmentTransformRules::KeepRelativeTransform);
	Barrel->SetupAttachment(Turret);

	MunitionSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("MunitionSpawnPoint"));
	MunitionSpawnPoint->AttachToComponent(Barrel, FAttachmentTransformRules::KeepRelativeTransform);
	MunitionSpawnPoint->SetupAttachment(Barrel);

	MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>(FName("MuzzleFlash"));
	MuzzleFlash->AttachToComponent(MunitionSpawnPoint, FAttachmentTransformRules::KeepRelativeTransform);
	MuzzleFlash->SetupAttachment(MunitionSpawnPoint);
	MuzzleFlash->bAutoActivate = false;
}

float AWeaponActor::GetAngleToTarget(AActor * Target)
{
	FVector TurretAimVector = MunitionSpawnPoint->GetForwardVector();

	FVector ActorVectorFromGun = (Target->GetActorLocation() - MunitionSpawnPoint->GetComponentLocation()).GetSafeNormal();

	float DotProduct = FVector::DotProduct(ActorVectorFromGun, TurretAimVector);

	float RadiansAngle = acosf(DotProduct);

	return FMath::RadiansToDegrees(RadiansAngle);
}

void AWeaponActor::AimAt(FVector Location)
{
	if (!ensure(Turret && Barrel)) return;

	FTransform BarrelTipTransform = MunitionSpawnPoint->GetComponentTransform();
	FVector AimDirection = BarrelTipTransform.InverseTransformPosition(Location).GetSafeNormal();

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

void AWeaponActor::AimAtActor(AActor * Actor)
{
	UE_LOG(LogTemp, Error, TEXT("AWeaponActor::AimAtActor - Not Overriden"));
}

void AWeaponActor::BeginFireWeapon()
{
	bAttemptingToFire = true;
}

void AWeaponActor::EndFireWeapon()
{
	bAttemptingToFire = false;
}

void AWeaponActor::FireIfOnTarget(AActor * Target)
{
	
}

void AWeaponActor::SetTargetActor(AActor * TargetActor)
{
	this->TargetActor = TargetActor;
}

void AWeaponActor::RotateTurret(float RelativeSpeed)
{
	float RotationSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto RotationChange = RotationSpeed * MaxTurretDegPerSec * GetWorld()->DeltaTimeSeconds;

	float RelYaw = Turret->GetRelativeTransform().GetRotation().Rotator().Yaw;
	
	auto NewRotation = RelYaw + RotationChange;

	NewRotation = FMath::Clamp(NewRotation, -MaxTurretSwivel, MaxTurretSwivel);

	Turret->SetRelativeRotation(FRotator(0, NewRotation, 0));
}

void AWeaponActor::RotateBarrel(float RelativeSpeed)
{
	float RotationSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto RotationChange = RotationSpeed * MaxBarrelDegPerSec * GetWorld()->DeltaTimeSeconds;

	float RelPitch = Barrel->GetRelativeTransform().GetRotation().Rotator().Pitch;

	auto NewRotation = RelPitch + RotationChange;

	NewRotation = FMath::Clamp(NewRotation, MinBarrelElevation, MaxBarrelElevation);

	Barrel->SetRelativeRotation(FRotator(NewRotation, 0, 0));
}

