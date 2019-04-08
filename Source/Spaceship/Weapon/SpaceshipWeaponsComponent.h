// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceshipWeaponsComponent.generated.h"

class UHardpointComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API USpaceshipWeaponsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceshipWeaponsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 *  Aims all weapons towards Location
	 *  @param Location - the vector to aim towards
	 */
	void AimAt(FVector Location);

	/*
	 *	Aims all weapons at the predicted location of the Actor.
	 *	Takes into account projectile travel time.
	 *	@param Actor - Actor being aimed at
	 */
	void AimAtActor(AActor * Actor);

	/*
	 *	Starts firing weapons
	 */
	UFUNCTION(BlueprintCallable)
	void BeginFireWeapons();

	/*
	 *	Stops firing weapons
	 */
	UFUNCTION(BlueprintCallable)
	void EndFireWeapons();

	/*
	 *  Used by AI controllers
	 *  Fires weapons if the weapon is aiming at the target
	 *  Stops the AI firing when off target
	 *  @param Target - the Actor which will be checked if weapons are aiming at
	 */
	UFUNCTION(BlueprintCallable)
	void FireIfOnTarget(AActor * Target);

	/*
	 *	Should be called upon death of spaceship. Destroys all weapon actors of this spaceship.
	 */
	void DestroyAllWeapons();

private:

	TArray<UHardpointComponent *> Hardpoints;
};
