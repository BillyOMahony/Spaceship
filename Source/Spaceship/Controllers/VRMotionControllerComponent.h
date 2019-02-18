// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "VRMotionControllerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACESHIP_API UVRMotionControllerComponent : public UMotionControllerComponent
{
	GENERATED_BODY()

public:
	UVRMotionControllerComponent();

	UFUNCTION(BlueprintCallable)
	void PickUp();

	UFUNCTION(BlueprintCallable)
	void Drop();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * HandMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent * PickupSphereCollider;

	AActor * HeldActor = nullptr;

	class AVRCharacter * OwnerCharacter;
};
