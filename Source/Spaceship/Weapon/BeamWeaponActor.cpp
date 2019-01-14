// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamWeaponActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"


ABeamWeaponActor::ABeamWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	LaserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Laser Mesh"));
	LaserMeshComponent->AttachToComponent(MunitionSpawnPoint, FAttachmentTransformRules::KeepRelativeTransform);
	LaserMeshComponent->SetupAttachment(MunitionSpawnPoint);
}

void ABeamWeaponActor::Tick(float DeltaTime)
{
	this->DeltaTime = DeltaTime;
	if (LaserMeshComponent) {
		if (bAttemptingToFire) {
			Fire();
		}
		else
		{
			LaserMeshComponent->SetWorldScale3D(FVector(0));
		}
	}
}

void ABeamWeaponActor::Fire()
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LaserMeshComponent->GetComponentLocation(),
		LaserMeshComponent->GetComponentLocation() + (LaserMeshComponent->GetForwardVector().GetSafeNormal() * BeamMaxLength),
		ECollisionChannel::ECC_Camera,
		FCollisionQueryParams(ECollisionChannel::ECC_Camera)
	);

	float BeamLength = BeamMaxLength;

	if(HitResult.GetActor())
	{
		FVector Direction;
		(HitResult.ImpactPoint - LaserMeshComponent->GetComponentLocation()).ToDirectionAndLength(Direction, BeamLength);

		FHitResult HitInfo;
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), DamagePerSecond * DeltaTime, GetInstigatorController(), this, UDamageType::StaticClass());
	}

	LaserMeshComponent->SetWorldScale3D(FVector(BeamLength, 10.f, 10.f));
}
