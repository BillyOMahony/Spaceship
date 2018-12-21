// Fill out your copyright notice in the Description page of Project Settings.

#include "VRSpaceshipController.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Weapon/SpaceshipWeaponsComponent.h"

void AVRSpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsAimLocation();
}

void AVRSpaceshipController::SetHandMeshes(UStaticMeshComponent * LeftHandMesh, UStaticMeshComponent * RightHandMesh)
{
	UE_LOG(LogTemp, Error, TEXT("Meshes Assigned"));
	this->LeftHandMesh = LeftHandMesh;
	this->RightHandMesh = RightHandMesh;
}

bool AVRSpaceshipController::GetAimLocation(FVector & HitLocation)
{
	if (!LeftHandMesh) return false;

	FHitResult HitResult;
	FVector StartLocation = LeftHandMesh->GetComponentLocation();
	FVector AimDirection = LeftHandMesh->GetComponentRotation().Vector().GetSafeNormal();

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + (AimDirection * RayTraceRange), ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		if (HitResult.GetActor() != GetPawn()) return true;
	}

	HitLocation = StartLocation + (AimDirection * RayTraceRange);
	return true;
}

void AVRSpaceshipController::AimTowardsAimLocation()
{
	if (!GetPawn()) { return; } // if not possessing 
	USpaceshipWeaponsComponent * WeaponsComponent = GetPawn()->FindComponentByClass<USpaceshipWeaponsComponent>();
	if (!ensure(WeaponsComponent)) { return; }

	FVector HitLocation; // Out parameter
	if (GetAimLocation(HitLocation)) {
		DrawLine(LeftHandMesh->GetComponentLocation(), HitLocation);
		WeaponsComponent->AimAt(HitLocation);
	}
}

void AVRSpaceshipController::DrawLine(FVector StartPoint, FVector EndPoint)
{
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Blue, false, -1, 0, 2.f);
}
