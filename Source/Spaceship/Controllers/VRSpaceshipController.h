// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VRSpaceshipController.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHIP_API AVRSpaceshipController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	/*
	 *
	 */
	UFUNCTION(BlueprintCallable)
	void SetHandMeshes(UStaticMeshComponent * LeftHandMesh, UStaticMeshComponent * RightHandMesh);

private:
	UPROPERTY(EditAnywhere)
	float RayTraceRange = 50000.f;

	UStaticMeshComponent * LeftHandMesh, * RightHandMesh;

	/*
	 *
	 */
	bool GetAimLocation(FVector &HitLocation);

	/*
	 *
	 */
	void AimTowardsAimLocation();

	/*
	 *
	 */
	void DrawLine(FVector StartPoint, FVector EndPoint);
};
