// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRPickupableActor.generated.h"

UCLASS()
class SPACESHIP_API AVRPickupableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRPickupableActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 *	returns whether or not this actor should be centered to the VR hand when picked up
	 *	or picked up where it is grabbed
	 */
	bool GetShouldCenterToHand();

	/*
	 *	@param IsPickedUp - Whether or not this PickupableActor is currently picked up
	 */
	virtual void SetIsPickedUp(bool IsPickedUp);

	/*
	 *	@return Whether or not this PickupableActor is currently picked up
	 */
	bool GetIsPickedUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 *	Repositions the root relative to the mesh, then attaches the mesh to the root.
	 *	Stops simulating physics.
	 */
	void HandleNotCenteredPickup();

	/*
	 *	Repositions the mesh relative to the root, then attaches the mesh to the root.
	 *	Stops simulating physics.
	 */
	void HandleCenteredPickup();

	UPROPERTY(VisibleAnywhere)
	USceneComponent * RootComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * PickupableMesh;

	UPROPERTY(EditAnywhere, Category = "Setup")
	bool bShouldCenterToHand = false;

	bool bIsPickedUp = false;

	bool bShouldSimulatePhysics = false;

private:
	UPROPERTY(EditAnywhere, Category = "Offset")
	FVector PickupableMeshRelativeLoc = FVector(0.f, 0.f, 0.f);
	
	UPROPERTY(EditAnywhere, Category = "Offset")
	FRotator PickupableMeshRelativeRot = FRotator(0.f);
};
