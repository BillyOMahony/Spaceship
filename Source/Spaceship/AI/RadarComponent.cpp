// Fill out your copyright notice in the Description page of Project Settings.

#include "RadarComponent.h"
#include "Components/SphereComponent.h"
#include "SpaceshipGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GameFramework/Pawn.h"
#include "Controllers/SpaceshipAIController.h"


// Sets default values for this component's properties
URadarComponent::URadarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void URadarComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!Cast<ASpaceshipAIController>(Cast<APawn>(GetOwner())->GetController()))
	{
		bRadarEnabled = false;
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

TArray<APawn*> URadarComponent::GetDetectedPawns()
{
	return DetectedPawns;
}

void URadarComponent::RadarBurst()
{
	// Clear DetectedPawns
	DetectedPawns.Empty();

	// Get Singleton List (GameMode)
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());
	TArray<APawn*> DetectablePawns = GameMode->GetRadarDetectablePawns();

	for(int32 i = 0; i < DetectablePawns.Num(); i++)
	{
		FString PawnName = DetectablePawns[i]->GetName();

		// If this pawn is not the owner pawn
		if(DetectablePawns[i] != Cast<APawn>(GetOwner()))
		{
			// Check if Pawn is within range, if so raycast to pawn to check if it is in view
			if (IsPawnWithinRange(DetectablePawns[i]) && IsPawnRadarVisible(DetectablePawns[i]))
			{
				DetectedPawns.Add(DetectablePawns[i]);
			}
		}
	}
}

bool URadarComponent::IsPawnWithinRange(APawn * Pawn)
{
	FVector RadarLoc = GetOwner()->GetActorLocation();
	FVector PawnLoc = Pawn->GetActorLocation();

	FVector OutDir;
	float OutLen;
	
	(RadarLoc - PawnLoc).ToDirectionAndLength(OutDir, OutLen);

	return OutLen < RadarRange;
}

bool URadarComponent::IsPawnRadarVisible(APawn * Pawn)
{
	FHitResult OutHit;
	FVector StartLoc = GetOwner()->GetActorLocation();
	FVector EndLoc = Pawn->GetActorLocation();
	
	const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;

	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = TraceTag;
	QueryParams.AddIgnoredActor(GetOwner());

	// the first actor hit by the line trace will be the Owner actor so we test against the second
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLoc, EndLoc, ECollisionChannel::ECC_Camera, QueryParams)) {

		if (Cast<APawn>(OutHit.Actor))
		{
			if (Cast<APawn>(OutHit.Actor) == Pawn)
			{
				return true;
			}
		}
	}

	return false;
}
