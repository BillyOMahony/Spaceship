// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Movement/SpaceshipMovementComponent.h"
#include "Weapon/SpaceshipWeaponsComponent.h"
#include "AIController.h"
#include "Engine/World.h"
#include "SpaceshipGameModeBase.h"

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

	// Register Pawn with GameMode RadarDetectablePawns
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->RegisterWithRadarDetectablePawns(this);
		GameMode->GetRadarDetectablePawns();
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("ASpaceshipPawn::BeginPlay"));
	}

	MovementComponent = FindComponentByClass<USpaceshipMovementComponent>();
	WeaponsComponent = FindComponentByClass<USpaceshipWeaponsComponent>();

	if(Cast<AAIController>(GetController()))
	{
		SetAIControlsPawn(true); 
	}
}

// Called to bind functionality to input
void ASpaceshipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called every frame
void ASpaceshipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->DeltaTime = DeltaTime;

	if (bAIControlsPawn) {
		HandleAIMovement();
	}
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

void ASpaceshipPawn::OnDeath()
{
	//TODO Implement

}

float ASpaceshipPawn::GetHealth()
{
	return Health;
}

void ASpaceshipPawn::MoveTowardsWayPoint()
{
	if(MovementComponent)
	{
		// Get relative vector of waypoint compared to spaceship
		FVector Direction = WayPoint - GetActorLocation();
		FVector DirectionToTurn = UKismetMathLibrary::InverseTransformDirection(GetActorTransform(), Direction).GetSafeNormal();

		// DirectionToTurn.Y = Roll. We want to aim for 0.
		MovementComponent->Roll(DeltaTime, DirectionToTurn.Y);

		MovementComponent->Pitch(DeltaTime, DirectionToTurn.Z);

		MovementComponent->SetThrottleUpPressed(true);

		// TODO Consider Adding in Vertical/ Horizontal movement

		// TODO Set Throttle based on distance to waypoint?? 
		// if close and throttle > x:
		//	  Throttle Down
		// else:
		//	  Throttle Up
	}
}

void ASpaceshipPawn::HandleAIMovement()
{
	if (bMovingTowardsWayPoint)
	{
		MoveTowardsWayPoint();
	}
	else
	{
		// TODO Movement Component should have better system for interacting with AI
		MovementComponent->SetThrottleDownPressed(true);
		MovementComponent->SetThrottleUpPressed(false);
	}
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

void ASpaceshipPawn::SetWayPoint(FVector WayPoint)
{
	this->WayPoint = WayPoint;
}

void ASpaceshipPawn::SetMovingTowardsWayPoint(bool MovingTowardsWayPoint)
{
	bMovingTowardsWayPoint = MovingTowardsWayPoint;
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

void ASpaceshipPawn::SetAIControlsPawn(bool AIControlsPawn)
{
	bAIControlsPawn = AIControlsPawn;
}

