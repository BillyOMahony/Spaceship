// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipPawn.h"

// Sets default values
ASpaceshipPawn::ASpaceshipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpaceshipPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceshipPawn::OnDeath()
{
	//TODO Implement
	UE_LOG(LogTemp, Error, TEXT("ASpaceshipPawn::OnDeath() - DEADDDDDD"));
		
}

float ASpaceshipPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;

	if(Health <= 0)
	{
		Health = 0;
		OnDeath();
	}

	return DamageAmount;
}

void ASpaceshipPawn::ToggleFirstPerson()
{
	bFirstPerson = !bFirstPerson;
	if (bVirtualReality) bFirstPerson = true;
}

void ASpaceshipPawn::SetIsVirtualReality(bool VirtualReality)
{
	bVirtualReality = VirtualReality;
	if (bVirtualReality) ToggleFirstPerson();
}

float ASpaceshipPawn::GetHealth()
{
	return Health;
}

// Called every frame
void ASpaceshipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpaceshipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

