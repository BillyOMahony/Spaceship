// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

class UCameraComponent;
class ACameraActor;

UCLASS()
class SPACESHIP_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Binds functionality to player input
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Returns the player camera
	 */
	UFUNCTION(BlueprintCallable)
	UCameraComponent * GetCamera();

	/*
	 * Instantly and directly teleports the character.
	 */
	void DirectTeleport(FTransform TeleportTransform);

	/*
	 *	Fades Camera out, teleports character, fades camera back in
	 *	@param TeleportTransform - The transform the player will be teleported to
	 */
	void TeleportCharacter(FTransform TeleportTransform);

	/*
	 *	Fades the player camera to colour
	 */
	void FadeToColor(float Duration, bool bHoldWhenFinished, FLinearColor Color);

private:
	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 0.25f;

	UPROPERTY(EditAnywhere)
	UCameraComponent * Camera;

	UPROPERTY(EditAnywhere)
	USceneComponent * VRRoot;

	UPROPERTY(EditAnywhere)
	float FadeDuration = .5f;

	/**
	 * Moves the character forward or backwards
	 * @param scale - speed multiplier which controls the speed and direction the character moves in. A negative scale moves the chatacter backwards
	 */
	UFUNCTION(BlueprintCallable)
	void MoveForward(float scale);

	/**
	 * Moves the character left or right
	 * @param scale - speed multiplier which controls the speed and direction the character moves in. A negative scale moves the character left
	 */
	UFUNCTION(BlueprintCallable)
	void MoveRight(float scale);

	/*
	 *	Rotates the camera 45 degrees in the desired direction
	 *	@param Direction - the direction rotation will be applied
	 */
	UFUNCTION(BlueprintCallable)
	void RotateCamera(float Direction);

	/*
	 *	Teleports the character to Location
	 *	Fades Camera back in
	 *	@param Location - The transform the character will be teleported to.
	 */
	void TeleportToLocation(FTransform Location, FLinearColor Color);

};
