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
	void SetIsPickedUp(bool IsPickedUp);

	/*
	 *	@return Whether or not this PickupableActor is currently picked up
	 */
	bool GetIsPickedUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent * SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * PickupableMesh;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	bool bShouldCenterToHand = false;

	bool bIsPickedUp = false;
};
