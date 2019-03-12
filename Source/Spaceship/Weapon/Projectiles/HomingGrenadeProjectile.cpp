// Fill out your copyright notice in the Description page of Project Settings.

#include "HomingGrenadeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/World.h"
#include "ProjectileDeathParticleActor.h"
#include "TimerManager.h"

// Sets default values
AHomingGrenadeProjectile::AHomingGrenadeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	AudioComponent->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	AudioComponent->SetupAttachment(Mesh);

	TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("Trail Component"));
	TrailComponent->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	TrailComponent->SetupAttachment(Mesh);
	TrailComponent->SetAutoActivate(false);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AHomingGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AHomingGrenadeProjectile::OnCompHit);

	// Automatically destroy this projectile after a certain amount of time
	FTimerHandle ProjectileTimeOutTimer;
	GetWorld()->GetTimerManager().SetTimer(
		ProjectileTimeOutTimer,
		this,
		&AHomingGrenadeProjectile::ExplodeProjectile,
		ProjectileAliveTime,
		false
	);

}

// Called every frame
void AHomingGrenadeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProjectileMovementComponent->HomingAccelerationMagnitude += ProjectileMovementComponent->HomingAccelerationMagnitude * HomingMagnitudeMultiplierPerSecond * DeltaTime;
}

void AHomingGrenadeProjectile::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("AHomingGrenadeProjectile::OnCompHit"));

	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("AHomingGrenadeProjectile::OnCompHit - %s"),*(OtherActor->GetName()));
	}

	ExplodeProjectile();
}

void AHomingGrenadeProjectile::LaunchProjectile(ACharacter * OwningCharacter, AActor * TargetActor)
{
	OwnerCharacter = OwningCharacter;
	
	ProjectileMovementComponent->Activate();
	
	// If there is a target we want to start tracking the target soon
	if (TargetActor) {
		// TODO Only activate this x time after launch
		this->TargetActor = TargetActor;
		
		FTimerHandle DelayedHomingActivationTimer;
		GetWorld()->GetTimerManager().SetTimer(
			DelayedHomingActivationTimer,
			this,
			&AHomingGrenadeProjectile::ActivateHoming,
			DelayedHomingActivationTime,
			false
		);
	}
}

void AHomingGrenadeProjectile::ExplodeProjectile()
{
	TArray<AActor *> IgnoredActors;

	if (Explosion) {
		GetWorld()->SpawnActor<AProjectileDeathParticleActor>(Explosion, GetActorLocation(), GetActorRotation());
	}

	UGameplayStatics::ApplyRadialDamageWithFalloff(
		GetWorld(),
		BaseDamage,
		MinDamage,
		GetActorLocation(),
		DamageInnerRadius,
		DamageOuterRadius,
		DamageFalloff,
		UDamageType::StaticClass(),
		IgnoredActors,
		this // TODO Swap this out with player character eventually
	);

	// TODO Spawn particle/audio
	// Consider creating Explosion class which automatically handles particle/explosion stuff
	Destroy();
}

void AHomingGrenadeProjectile::ActivateHoming()
{
	ProjectileMovementComponent->HomingTargetComponent = TargetActor->GetRootComponent();
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = InitialHomingMagnitude;

	if (MissileLaunchSound) {
		AudioComponent->SetSound(MissileLaunchSound);
		AudioComponent->Play();
	}

	if (TrailComponent) {
		TrailComponent->Activate();
	}
}

