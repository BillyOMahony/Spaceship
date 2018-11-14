// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceshipMovementComponent.generated.h"

class UMainThruster;
class USecondaryThruster;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API USpaceshipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceshipMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 *	Adds to MainThrottle
	 *	Clamps value between 0 and 1
	 *	@param ThrottleToAdd - the throttle to add to MainThrottle 
	 */
	UFUNCTION(BlueprintCallable)
	void AddMainThrottle(float ThrottleToAdd);

	/*
	 *	@param SpaceshipHull - The spaceship hull which forces will be applied to
	 */
	UFUNCTION(BlueprintCallable)
	void SetSpaceshipHull(UStaticMeshComponent * SpaceshipHull);

	void MoveForward(float DeltaTime);

	void Stabilise();

private:
	
	float MainThrottle;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UMainThruster>> MainThrusters;

	UStaticMeshComponent * SpaceshipHull;
};
