// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceshipThrusterComponent.generated.h"

UENUM(BlueprintType)
enum class EThrusterDirection : uint8 {
	Forward		UMETA(DisplayName = "Forwards"),
	Backwards	UMETA(DisplayName = "Backwards"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right"),
	Up			UMETA(DisplayName = "Up"),
	Down		UMETA(DisplayName = "Down")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API USpaceshipThrusterComponent : public UActorComponent
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

	UPROPERTY(EditAnywhere)
	float Throttle = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxVelocity = 10000.f;

	UPROPERTY(EditAnywhere)
	float AccelerationForce = 5000000000.f;

	UPROPERTY(EditAnywhere)
	float DecelerationMultiplier = 2.5f;

	UPROPERTY(EditAnywhere)
	EThrusterDirection ThrustDirection = EThrusterDirection::Forward;

	UStaticMeshComponent * SpaceshipHull;

private:	


		
};
