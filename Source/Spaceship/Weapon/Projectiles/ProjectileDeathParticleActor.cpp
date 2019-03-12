// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileDeathParticleActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"


// Sets default values
AProjectileDeathParticleActor::AProjectileDeathParticleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(FName("Projectile Death Particle"));
	SetRootComponent(DeathParticleSystem);

	DeathParticleSystem->SetAutoActivate(false);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	AudioComponent->AttachToComponent(DeathParticleSystem, FAttachmentTransformRules::KeepRelativeTransform);
	AudioComponent->SetupAttachment(DeathParticleSystem);
}

// Called when the game starts or when spawned
void AProjectileDeathParticleActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (DeathAudio) {
		AudioComponent->SetSound(DeathAudio);
		AudioComponent->Play();
	}
	
	if (DeathParticleSystem) {
		DeathParticleSystem->Activate();
	}
}

// Called every frame
void AProjectileDeathParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!(AudioComponent->IsPlaying() || DeathParticleSystem->bIsActive)) {
		Destroy();
	}
}

