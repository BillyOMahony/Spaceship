// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPickupableActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVRPickupableActor::AVRPickupableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName("Scene Root"));
	SetRootComponent(SceneRoot);

	PickupableMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Pickupable Mesh"));
	PickupableMesh->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	PickupableMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AVRPickupableActor::BeginPlay()
{
	Super::BeginPlay();

	PickupableMeshRelativeLoc = SceneRoot->GetComponentLocation() - PickupableMesh->GetComponentLocation();
	bShouldSimulatePhysics = PickupableMesh->IsSimulatingPhysics();
}

bool AVRPickupableActor::GetShouldCenterToHand()
{
	return bShouldCenterToHand;
}

void AVRPickupableActor::SetIsPickedUp(bool IsPickedUp)
{
	bIsPickedUp = IsPickedUp;

	if (bIsPickedUp && bShouldSimulatePhysics) {
		SceneRoot->SetWorldLocation(PickupableMesh->GetComponentLocation() - PickupableMeshRelativeLoc);
		PickupableMesh->SetSimulatePhysics(false);
		PickupableMesh->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepWorldTransform);
	}
	else {
		PickupableMesh->SetSimulatePhysics(bShouldSimulatePhysics);
	}
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

