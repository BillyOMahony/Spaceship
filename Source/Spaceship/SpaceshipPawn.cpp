// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceshipPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Movement/SpaceshipMovementComponent.h"
#include "Weapon/SpaceshipWeaponsComponent.h"
#include "AIController.h"
#include "Engine/World.h"
#include "SpaceshipGameModeBase.h"
#include "Components/RadarRegistrarComponent.h"

// Sets default values
ASpaceshipPawn::ASpaceshipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RadarRegistrarComponent = CreateDefaultSubobject<URadarRegistrarComponent>(FName(TEXT("Radar Registrar Component")));
}

// Called when the game starts or when spawned
void ASpaceshipPawn::BeginPlay()
{
	Super::BeginPlay();

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
		if(!TargetActor)
		{
			DoNotFire();
		}
	}
}

float ASpaceshipPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("ASpaceshipPawn::TakeDamage - %f"), DamageAmount);

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
	// Register Pawn with GameMode RadarDetectablePawns
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->DeRegisterFromRadarDetectableActors(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASpaceshipPawn::OnDeath - Cannot Find GameMode"));
	}

	WeaponsComponent->DestroyAllWeapons();

	Destroy();
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

		MovementComponent->ThrottleUp(DeltaTime, 1);

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
	else if(TargetActor)
	{
		MoveTowardsTargetActor();
	}
	else
	{
		MovementComponent->ThrottleDown(DeltaTime, 1);
	}
}

void ASpaceshipPawn::MoveTowardsTargetActor()
{
	if(MovementComponent && TargetActor)
	{
		// Get relative vector of TargetActor compared to spaceship
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
		FVector DirectionToTurn = UKismetMathLibrary::InverseTransformDirection(GetActorTransform(), Direction).GetSafeNormal();

		// Pitch and Roll
		MovementComponent->Roll(DeltaTime, DirectionToTurn.Y);

		MovementComponent->Pitch(DeltaTime, DirectionToTurn.Z);

		MovementComponent->ThrottleUp(DeltaTime, 1);

		/*
		// Accelerate or Decelerate ?
		float Throttle = MovementComponent->GetMainThrottle();

		FVector OutDir;
		float OutLen;

		Direction.ToDirectionAndLength(OutDir, OutLen);

		
		// TODO Remove Magic Numbers
		float IdealThrottle = (OutLen - 10000) / (30000 - 10000);
		float ClampedIdealThrottle = FMath::Clamp(IdealThrottle, 0.f, 1.f);

		// Set Throttle
		if(Throttle > ClampedIdealThrottle)
		{
			MovementComponent->SetThrottleDownPressed(true);
			MovementComponent->SetThrottleUpPressed(false);
		}
		else
		{
			MovementComponent->SetThrottleDownPressed(false);
			MovementComponent->SetThrottleUpPressed(true);
		}
		*/
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

void ASpaceshipPawn::SetTargetActor(AActor* Target)
{
	TargetActor = Target;
}

void ASpaceshipPawn::DoNotFire()
{
	if (!ensure(WeaponsComponent)) return;
	WeaponsComponent->EndFireWeapons();
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