// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceshipController.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API ASpaceshipController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;


private:
	/*
	 *	@return the screen coordinates of the mouse as a percentage
	 */
	FVector2D GetMouseCoordinates();
};

