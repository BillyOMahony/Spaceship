// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RadarComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API URadarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadarComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	/*
	 *	Populates the OverlappedPawns and VisiblePawns Arrays
	 */
	void RadarBurst();

	UPROPERTY(EditAnywhere, Category = "Radar")
	float RadarRange = 10000.f;

	UPROPERTY(EditAnywhere, Category = "Radar")
	float RadarBurstRate = 1.f;

	TArray<APawn *> OverlappedPawns;

	TArray<APawn*> VisiblePawns;


};
