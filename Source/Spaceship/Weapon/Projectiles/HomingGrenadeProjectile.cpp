// Fill out your copyright notice in the Description page of Project Settings.

#include "HomingGrenadeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

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
	
}

// Called every frame
void AHomingGrenadeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHomingGrenadeProjectile::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

}

void AHomingGrenadeProjectile::LaunchProjectile(ACharacter * OwningCharacter, AActor * TargetActor)
{
	OwnerCharacter = OwningCharacter;
	
	ProjectileMovementComponent->Activate();
	if(TargetActor)	ProjectileMovementComponent->HomingTargetComponent = TargetActor->GetRootComponent();
}

