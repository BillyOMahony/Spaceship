// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "Components/StaticMeshComponent.h"

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

}

