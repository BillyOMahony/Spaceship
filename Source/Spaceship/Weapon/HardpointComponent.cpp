// Fill out your copyright notice in the Description page of Project Settings.

#include "HardpointComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "WeaponActor.h"

// Sets default values for this component's properties
UHardpointComponent::UHardpointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UHardpointComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UHardpointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHardpointComponent::SpawnWeapon()
{
	if (!Weapon) return;
	FActorSpawnParameters SpawnParams;
	SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActor>(Weapon, FVector(0), FRotator(0));
	SpawnedWeapon->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	//SpawnedWeapon->SetupAttachment();
}

