// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "HomingGrenadeProjectile.generated.h"

UCLASS()
class SPACESHIP_API AHomingGrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingGrenadeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void LaunchProjectile(ACharacter * OwningCharacter, AActor * TargetActor);

private:
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent * SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 10.f;

	ACharacter * OwnerCharacter;
	
	AActor * TargetActor;

};
