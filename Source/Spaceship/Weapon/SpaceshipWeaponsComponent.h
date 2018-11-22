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
	 * TODO
	 */
	void AimAt(FVector Location);

	/*
	 *	TODO
	 */
	UFUNCTION(BlueprintCallable)
	void Fire();

private:

	TArray<UHardpointComponent *> Hardpoints;
};
