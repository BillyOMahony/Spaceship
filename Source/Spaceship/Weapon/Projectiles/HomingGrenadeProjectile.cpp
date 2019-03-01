// Fill out your copyright notice in the Description page of Project Settings.

#include "HomingGrenadeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AHomingGrenadeProjectile::AHomingGrenadeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetSimulatePhysics(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AHomingGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();

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

	ExplodeProjectile();
}

void AHomingGrenadeProjectile::LaunchProjectile(ACharacter * OwningCharacter, AActor * TargetActor)
{
	OwnerCharacter = OwningCharacter;
	
	ProjectileMovementComponent->Activate();
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
	UE_LOG(LogTemp, Warning, TEXT("AHomingGrenadeProjectile::ExplodeProjectile - Dead"));
	// TODO Spawn particle/audio
	// Consider creating Explosion class which automatically handles particle/explosion stuff
	Destroy();
}

void AHomingGrenadeProjectile::ActivateHoming()
{
	ProjectileMovementComponent->HomingTargetComponent = TargetActor->GetRootComponent();
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = InitialHomingMagnitude;
}

