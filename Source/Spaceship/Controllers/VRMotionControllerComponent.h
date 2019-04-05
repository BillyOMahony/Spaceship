// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "VRMotionControllerComponent.generated.h"

USTRUCT()
struct FHeldActorInfo
{
	GENERATED_BODY()

	UPROPERTY()
	AActor * HeldActor;

	UPROPERTY()
	bool bWasSimulatingPhysics;

	void SetHeldActor(AActor * NewHeldActor) {
		HeldActor = NewHeldActor;
	}

	void SetWasSimulatingPhysics(bool WasSimulatingPhysics) {
		bWasSimulatingPhysics = WasSimulatingPhysics;
	}

	AActor * GetHeldActor() {
		return HeldActor;
	}

	bool GetWasSimulatingPhysics() {
		return bWasSimulatingPhysics;
	}

	FHeldActorInfo() {
		HeldActor = nullptr;
		bWasSimulatingPhysics = false;
	}
};

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

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void EndFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * HandMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent * PickupSphereCollider;

	class AVRCharacter * OwnerCharacter;

	FHeldActorInfo HeldActorInfo;
};
