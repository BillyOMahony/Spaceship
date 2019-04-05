// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGun.h"
#include "Weapon/Ammo/AmmoActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AVRGun::AVRGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("Projectile Spawn Point"));
	ProjectileSpawnPoint->AttachToComponent(PickupableMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileSpawnPoint->SetupAttachment(PickupableMesh);

	AmmoAttachmentPointCollider = CreateDefaultSubobject<UBoxComponent>(FName("Ammo Attachment Point Collider"));
	AmmoAttachmentPointCollider->AttachToComponent(PickupableMesh, FAttachmentTransformRules::KeepRelativeTransform);
	AmmoAttachmentPointCollider->SetupAttachment(PickupableMesh);
	AmmoAttachmentPointCollider->ComponentTags.Add(FName("AmmoAttachmentPoint"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	AudioComponent->AttachToComponent(ProjectileSpawnPoint, FAttachmentTransformRules::KeepRelativeTransform);
	AudioComponent->SetupAttachment(ProjectileSpawnPoint);
	AudioComponent->SetAutoActivate(false);
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
	
}

void AVRGun::AttachAmmoCartridge(AAmmoActor * AmmoCartridge)
{
	AmmoActor = AmmoCartridge;
	AmmoCartridge->AttachToComponent(PickupableMesh, FAttachmentTransformRules::KeepWorldTransform, FName("AmmoAttachmentPoint"));
	AmmoCartridge->SetActorRelativeLocation(FVector(0.f));
	AmmoCartridge->SetActorRelativeRotation(FRotator(0.f));
}

void AVRGun::DetachAmmoCartridge()
{
	AmmoActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AmmoActor = nullptr;
}

void AVRGun::AllowFire()
{
	bCanFire = true;
}