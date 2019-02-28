// Fill out your copyright notice in the Description page of Project Settings.

#include "VRMotionControllerComponent.h"
#include "Components/SphereComponent.h"
#include "Pickupable/VRPickupableActor.h"
#include "Weapon/VRGun.h"
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
	PickupSphereCollider->GetOverlappingActors(OverlappingActors, TSubclassOf<AVRPickupableActor>());

	for (int32 i = 0; i < OverlappingActors.Num(); i++) 
	{
		// if not the player character
		AVRPickupableActor * OverlappedActor = Cast<AVRPickupableActor>(OverlappingActors[i]);

		if (OverlappedActor) {
			if (!OverlappedActor->GetIsPickedUp()) {
				OverlappedActor->SetIsPickedUp(true);
				OverlappedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
				if (OverlappedActor->GetShouldCenterToHand()) {
					OverlappedActor->SetActorRelativeLocation(FVector(0.f));
					OverlappedActor->SetActorRelativeRotation(FQuat(0.f, 0.f, 0.f, 0.f));
				}
				HeldActorInfo.SetHeldActor(OverlappedActor);
				break;
			}
		}
	}
}

void UVRMotionControllerComponent::Drop()
{
	AActor * HeldActor = HeldActorInfo.GetHeldActor();

	if (!HeldActor) return;

	HeldActor->DetachRootComponentFromParent(true);
	Cast<AVRPickupableActor>(HeldActor)->SetIsPickedUp(false);
}

void UVRMotionControllerComponent::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("UVRMotionControllerComponent::Fire"));
	if (HeldActorInfo.GetHeldActor()) {
		AVRGun * Gun = Cast<AVRGun>(HeldActorInfo.GetHeldActor());
		if (Gun) {
			Gun->Fire();
		}
	}
}
