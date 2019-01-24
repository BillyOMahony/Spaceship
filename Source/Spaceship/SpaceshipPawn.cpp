// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Movement/SpaceshipMovementComponent.h"
#include "Weapon/SpaceshipWeaponsComponent.h"

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

	MovementComponent = FindComponentByClass<USpaceshipMovementComponent>();
	WeaponsComponent = FindComponentByClass<USpaceshipWeaponsComponent>();
}

void ASpaceshipPawn::AimTowardsTarget()
{
	if (TargetActor && WeaponsComponent) {
		WeaponsComponent->AimAt(TargetActor->GetActorLocation());
	}
}

void ASpaceshipPawn::FireAtTarget()
{
	if (TargetActor && WeaponsComponent) {
		WeaponsComponent->FireIfOnTarget(TargetActor);
	}
}

// Called every frame
void ASpaceshipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->DeltaTime = DeltaTime;
}

void ASpaceshipPawn::OnDeath()
{
	//TODO Implement
		
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

void ASpaceshipPawn::MoveTowardsPoint(FVector Point)
{
	if(MovementComponent)
	{
		// Get relative vector of waypoint compared to spaceship
		FVector Direction = Point - GetActorLocation();
		FVector DirectionToTurn = UKismetMathLibrary::InverseTransformDirection(GetActorTransform(), Direction).GetSafeNormal();

		// DirectionToTurn.Y = Roll. We want to aim for 0.
		MovementComponent->Roll(DeltaTime, DirectionToTurn.Y);

		MovementComponent->Pitch(DeltaTime, DirectionToTurn.Z);

		MovementComponent->SetThrottleUpPressed(true);

		// TODO Set Throttle based on distance to waypoint
		// Consider doing that elsewhere (Behaviour Tree)

	}
}

// Called to bind functionality to input
void ASpaceshipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

