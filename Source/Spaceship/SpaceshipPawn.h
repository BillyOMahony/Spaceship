// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceshipPawn.generated.h"

UCLASS()
class SPACESHIP_API ASpaceshipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceshipPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	 *	Sets whether the AI controls this pawn
	 *	TODO Look for better solution to this dirt
	 */
	void SetAIControlsPawn(bool AIControlsPawn);

	/*
	 *	Applies damage to this spaceship
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/*
	 *	Toggles the camera
	 *	Switches between third and first person
	 */
	UFUNCTION(BlueprintCallable)
	void ToggleFirstPerson();

	/*
	 *	Sets whether or not VR is in use
	 */
	UFUNCTION(BlueprintCallable)
	void SetIsVirtualReality(bool VirtualReality);

	/*
	 *	@return Spaceship health value
	 */
	UFUNCTION(BlueprintCallable)
	float GetHealth();

	/*
	 *	Moves this pawn towards the waypoint
	 */
	void MoveTowardsWayPoint();

	/*
	 *	Aims towards TargetActor and fires at it if aiming at it
	 */
	void AimTowardsTarget();

	/*
	 *	Fires at the target if the weapon is on target
	 */
	void FireAtTarget();

	/*
	 *	Sets the Waypoint for this Spaceship to follow
	 */
	void SetWayPoint(FVector WayPoint);

	/*
	 *	Sets whether this Spaceship should fly towards its current waypoint
	 */
	void SetMovingTowardsWayPoint(bool MovingTowardsWayPoint);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 *	Handles death of a pawn
	 */
	void OnDeath();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFirstPerson = true;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bVirtualReality = true;

	float Health = 100.f;

private:

	bool bAIControlsPawn = false;

	FVector WayPoint;

	bool bMovingTowardsWayPoint = false;

	UPROPERTY(EditAnywhere)
	AActor * TargetActor;

	class USpaceshipMovementComponent * MovementComponent;

	class USpaceshipWeaponsComponent * WeaponsComponent;

	float DeltaTime = 0;
};
