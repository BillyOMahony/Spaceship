// Fill out your copyright notice in the Description page of Project Settings.

#include "VRMotionControllerComponent.h"
#include "Components/SphereComponent.h"
#include "Pawns/VRCharacter.h"

UVRMotionControllerComponent::UVRMotionControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	HandMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("HandMesh"));
	HandMesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	HandMesh->SetupAttachment(this);

	PickupSphereCollider = CreateDefaultSubobject<USphereComponent>(FName("Pickup Sphere Collider"));
	PickupSphereCollider->AttachToComponent(HandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	PickupSphereCollider->SetupAttachment(HandMesh);
}

void UVRMotionControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<AVRCharacter>(GetOwner());
	if (!OwnerCharacter) {
		UE_LOG(LogTemp, Error, TEXT("UVRMotionControllerComponent::BeginPlay - Cannot cast %s to AVRCharacter"));
	}
}

void UVRMotionControllerComponent::PickUp()
{
	// First Log
	TArray<AActor *> OverlappingActors;
	PickupSphereCollider->GetOverlappingActors(OverlappingActors);

	for (int32 i = 0; i < OverlappingActors.Num(); i++) 
	{
		// if not the player character
		if (!Cast<AVRCharacter>(OverlappingActors[i])) {
			OverlappingActors[i]->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			HeldActor = OverlappingActors[i];
			break;
		}
	}
}

void UVRMotionControllerComponent::Drop()
{
	if (!HeldActor) return;

	HeldActor->DetachRootComponentFromParent(true);

}