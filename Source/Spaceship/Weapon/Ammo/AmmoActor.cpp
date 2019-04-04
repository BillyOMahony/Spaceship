// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoActor.h"
#include "Weapon/VRGun.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAmmoActor::AAmmoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAmmoActor::SetIsPickedUp(bool IsPickedUp)
{
	bIsPickedUp = IsPickedUp;

	// If has just been dropped
	if (!bIsPickedUp) {
		// Search for attachment point
		TArray<UPrimitiveComponent*> OverlappingComps;
		GetOverlappingComponents(OverlappingComps);
		bool bAttachmentPointFound = false;

		for (int32 i = 0; i < OverlappingComps.Num(); i++) {
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *(OverlappingComps[i]->GetName()));

			if (OverlappingComps[i]->ComponentHasTag("AmmoAttachmentPoint")) {
				bAttachmentPointFound = true;
				AttachedGun = Cast<AVRGun>(OverlappingComps[i]->GetOwner());
				if (AttachedGun) {
					HandleCenteredPickup();
					AttachedGun->AttachAmmoCartridge(this);
					PickupableMesh->SetCollisionProfileName("OverlapAll");
					return;
				}
			}
		}

		// if no attachment point
		if (bShouldSimulatePhysics) {
			PickupableMesh->SetSimulatePhysics(bShouldSimulatePhysics);
			PickupableMesh->SetCollisionProfileName("VRPickupable");
		}
	}
	// If has just been picked up
	else if (bShouldSimulatePhysics && bIsPickedUp) {

		if (AttachedGun) {
			AttachedGun->DetachAmmoCartridge();
			AttachedGun = nullptr;
		}

		if (!bShouldCenterToHand) {
			HandleNotCenteredPickup();
		}
		else {
			HandleCenteredPickup();
		}
	}
}

int32 AAmmoActor::GetAmmo()
{
	return Ammo;
}

void AAmmoActor::FireRound()
{
	Ammo--;
	AnimateCartridge(AnimationTime);
}

// Called when the game starts or when spawned
void AAmmoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

