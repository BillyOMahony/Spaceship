// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileDeathParticleActor.generated.h"

UCLASS()
class SPACESHIP_API AProjectileDeathParticleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileDeathParticleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent * DeathParticleSystem;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent * AudioComponent;

	UPROPERTY(EditAnywhere)
	class USoundBase * DeathAudio;
};
