// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "HardpointComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API UHardpointComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHardpointComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 *	Spawns the associated UWeaponComponent if it exists
	 */
	void SpawnWeapon();

	void AimWeaponAt(FVector Location);

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<class AWeaponActor> Weapon;

	AWeaponActor * SpawnedWeapon;
};
