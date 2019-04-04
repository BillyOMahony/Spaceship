// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPickupableActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVRPickupableActor::AVRPickupableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("Scene Root"));
	SetRootComponent(RootComp);

	PickupableMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Pickupable Mesh"));
	PickupableMesh->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
	PickupableMesh->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AVRPickupableActor::BeginPlay()
{
	Super::BeginPlay();

	PickupableMesh->SetCollisionProfileName("VRPickupable");

	PickupableMeshRelativeLoc = PickupableMesh->GetComponentLocation() - RootComp->GetComponentLocation();
	PickupableMeshRelativeRot = PickupableMesh->GetComponentRotation() - RootComp->GetComponentRotation();

	bShouldSimulatePhysics = PickupableMesh->IsSimulatingPhysics();
}

bool AVRPickupableActor::GetShouldCenterToHand()
{
	return bShouldCenterToHand;
}

void AVRPickupableActor::SetIsPickedUp(bool IsPickedUp)
{
	bIsPickedUp = IsPickedUp;

	if (bIsPickedUp && bShouldSimulatePhysics && !bShouldCenterToHand) {
		HandleNotCenteredPickup();
	}
	else if (bIsPickedUp && bShouldSimulatePhysics && bShouldCenterToHand) {
		HandleCenteredPickup();
	}
	else if(bShouldSimulatePhysics){
		PickupableMesh->SetSimulatePhysics(bShouldSimulatePhysics);
	}
}

void AVRPickupableActor::HandleCenteredPickup()
{
	PickupableMesh->SetSimulatePhysics(false);
	PickupableMesh->AttachToComponent(RootComp, FAttachmentTransformRules::KeepWorldTransform);
	PickupableMesh->SetRelativeLocationAndRotation(PickupableMeshRelativeLoc, PickupableMeshRelativeRot);
}

void AVRPickupableActor::HandleNotCenteredPickup()
{
	PickupableMesh->SetSimulatePhysics(false);
	RootComp->SetWorldLocation(PickupableMesh->GetComponentLocation() - PickupableMeshRelativeLoc);
	RootComp->SetWorldRotation(PickupableMesh->GetComponentRotation() - PickupableMeshRelativeRot);
	PickupableMesh->AttachToComponent(RootComp, FAttachmentTransformRules::KeepWorldTransform);
}

bool AVRPickupableActor::GetIsPickedUp()
{
	return bIsPickedUp;
}

// Called every frame
void AVRPickupableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

