// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGun.h"

// Sets default values
AVRGun::AVRGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	UE_LOG(LogTemp, Error, TEXT("AVRGun::Fire - Called, Unimplemented"))
}

void AVRGun::PickUp(UActorComponent * Component)
{
	
}

