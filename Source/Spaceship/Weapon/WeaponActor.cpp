// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Projectile.h"


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

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->AttachToComponent(Barrel, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileSpawnPoint->SetupAttachment(Barrel);
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::AimAt(FVector Location)
{
	if (!ensure(Turret && Barrel)) return;

	FTransform BarrelTipTransform = ProjectileSpawnPoint->GetComponentTransform();
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

void AWeaponActor::Fire()
{
	if(Projectile)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor(Projectile, &SpawnLocation, &SpawnRotation, SpawnParams);
	}
}

void AWeaponActor::SetOwningActor(AActor * OwningActor)
{
	this->OwningActor = OwningActor;
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

