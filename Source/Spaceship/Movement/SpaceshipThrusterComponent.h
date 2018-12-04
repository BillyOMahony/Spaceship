// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SpaceshipThrusterComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API USpaceshipThrusterComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceshipThrusterComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	*	@param Hull - The static mesh component which represents the main body of this spaceship
	*/
	UFUNCTION(BlueprintCallable)
	void SetSpaceshipHull(UStaticMeshComponent * Hull);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float Throttle = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxVelocity = 2500.f;

	UPROPERTY(EditAnywhere)
	float AccelerationForce = 1500000000.f;

	UPROPERTY(EditAnywhere)
	float DecelerationMultiplier = 2.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent * ParticleSystem;

	UStaticMeshComponent * SpaceshipHull;
private:	
		
};
