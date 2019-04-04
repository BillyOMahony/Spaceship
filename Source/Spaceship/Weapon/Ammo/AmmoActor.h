// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickupable/VRPickupableActor.h"
#include "AmmoActor.generated.h"

UCLASS()
class SPACESHIP_API AAmmoActor : public AVRPickupableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoActor();

	virtual void Tick(float DeltaTime) override;

	/*
	 *	Sets whether or not this actor is picked up and handles physics and other information accordingly
	 */
	void SetIsPickedUp(bool IsPickedUp) override;

	/*
	 * @return Ammo amount
	 */
	int32 GetAmmo();

	/*
	 *	Decrements the ammo count
	 */
	void FireRound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animation")
	void AnimateCartridge(float AnimationTime);

private:
	UPROPERTY(EditDefaultsOnly)
	int32 Ammo = 6;

	UPROPERTY(EditAnywhere)
	float AnimationTime =.5f; 

	class AVRGun * AttachedGun;
};
