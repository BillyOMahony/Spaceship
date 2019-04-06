// Fill out your copyright notice in the Description page of Project Settings.

#include "RadarComponent.h"
#include "Components/SphereComponent.h"
#include "SpaceshipGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceshipPawn.h"
#include "GameFramework/Pawn.h"
#include "Controllers/SpaceshipAIController.h"
#include "GameFramework/Actor.h"
#include "Components/RadarRegistrarComponent.h"


// Sets default values for this component's properties
URadarComponent::URadarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

AActor * URadarComponent::GetClosestActor()
{
	if(DetectedActors.Num() > 0)
	{
		int32 ClosestIndex = 0;

		FVector RadarLoc = GetOwner()->GetActorLocation();
		FVector PawnLoc = DetectedActors[0]->GetActorLocation();

		FVector OutDir;
		float OutLen;

		(RadarLoc - PawnLoc).ToDirectionAndLength(OutDir, OutLen);
		float ClosestDst = OutLen;

		for(int32 i = 1; i < DetectedActors.Num(); i++)
		{
			PawnLoc = DetectedActors[i]->GetActorLocation();
			(RadarLoc - PawnLoc).ToDirectionAndLength(OutDir, OutLen);
			if(OutLen < ClosestDst)
			{
				ClosestDst = OutLen;
				ClosestIndex = i;
			}
		}

		return DetectedActors[ClosestIndex];
	}

	return nullptr;
}

void URadarComponent::SetIgnorePlayer(bool IgnorePlayer)
{
	bIgnorePlayer = IgnorePlayer;
}

// Called when the game starts
void URadarComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO First if needs to be replaced
	if (Cast<APawn>(GetOwner())) {
		if (!Cast<ASpaceshipAIController>(Cast<APawn>(GetOwner())->GetController()))
		{
			bRadarEnabled = false;
		}
	}

}

// Called every frame
void URadarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bRadarEnabled) {
		RadarBurst();
	}
}

TArray<AActor*> URadarComponent::GetDetectedActors() const
{
	return DetectedActors;
}

void URadarComponent::RadarBurst()
{
	EFactionEnum MyFaction;

	// TODO Store EFactionEnum in a better, consistant place
	// Something like, Cast<APawn>(GetOwner())->GetComponent(FactionComponent)->GetFaction()
	URadarRegistrarComponent * RadarRegistrarComponent = GetOwner()->FindComponentByClass<URadarRegistrarComponent>();
	if (RadarRegistrarComponent) {
		MyFaction = RadarRegistrarComponent->GetFaction();
	}

	// Clear DetectedPawns
	DetectedActors.Empty();

	// Get Singleton List (GameMode)
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());
	TArray<AActor*> DetectableActors = GameMode->GetOpposingRadarDetectableActors(MyFaction);

	for(int32 i = 0; i < DetectableActors.Num(); i++)
	{
		FString PawnName = DetectableActors[i]->GetName();

		// If this pawn is not the owner pawn
		if(DetectableActors[i] != Cast<AActor>(GetOwner()))
		{
			// Check if Actor is within range, if so raycast to pawn to check if it is in view
			if (IsActorWithinRange(DetectableActors[i]) && IsActorRadarVisible(DetectableActors[i]))
			{
				DetectedActors.Add(DetectableActors[i]);
			}
		}
	}
}

bool URadarComponent::IsActorWithinRange(AActor * Actor) const
{
	FVector RadarLoc = GetOwner()->GetActorLocation();
	FVector PawnLoc = Actor->GetActorLocation();

	FVector OutDir;
	float OutLen;
	
	(RadarLoc - PawnLoc).ToDirectionAndLength(OutDir, OutLen);

	return OutLen < RadarRange;
}

bool URadarComponent::IsActorRadarVisible(AActor * Actor) const
{
	FHitResult OutHit;
	FVector StartLoc = GetOwner()->GetActorLocation();
	FVector EndLoc = Actor->GetActorLocation();
	
	const FName TraceTag("MyTraceTag");
	//GetWorld()->DebugDrawTraceTag = TraceTag;

	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = TraceTag;
	QueryParams.AddIgnoredActor(GetOwner());

	// TODO Refactor
	if (bIgnorePlayer) {
		QueryParams.AddIgnoredActor(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	// the first actor hit by the line trace will be the Owner actor so we test against the second
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLoc, EndLoc, ECollisionChannel::ECC_Camera, QueryParams)) {

		if (OutHit.Actor == Actor)
		{
			return true;
		}
	}

	return false;
}
