// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceshipGameModeBase.h"
#include "RadarRegistrarComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHIP_API URadarRegistrarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadarRegistrarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	EFactionEnum GetFaction();

	UFUNCTION(BlueprintCallable)
	ETargetTypeEnum GetTargetType();

private:
	void RegisterPawn();

	UPROPERTY(EditAnywhere, Category = "Faction")
	EFactionEnum Faction;

	UPROPERTY(EditAnywhere, Category = "TargetType")
	ETargetTypeEnum TargetType = ETargetTypeEnum::TT_Ground;

};
