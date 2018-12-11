// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceshipPawn.generated.h"

UCLASS()
class SPACESHIP_API ASpaceshipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceshipPawn();

	UFUNCTION(BlueprintCallable)
	void ToggleFirstPerson();

	UFUNCTION(BlueprintCallable)
	void SetIsVirtualReality(bool VirtualReality);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFirstPerson = true;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bVirtualReality = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
