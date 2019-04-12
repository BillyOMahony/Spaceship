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
#include "Engine/World.h"
#include "TimerManager.h"


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

	// TODO First if needs to be replaced
	if (Cast<APawn>(GetOwner())) {
		if (!Cast<ASpaceshipAIController>(Cast<APawn>(GetOwner())->GetController()))
		{
			bRadarEnabled = false;
		}
	}

	FTimerHandle RadarBurstTimerHandle;

	float RandomInitialTimer = FMath::RandRange(0.f, RadarBurstRate);

	GetWorld()->GetTimerManager().SetTimer(
		RadarBurstTimerHandle,
		this,
		&URadarComponent::RadarBurst,
		RandomInitialTimer,
		false
	);

}

// Called every frame
void URadarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

TArray<AActor*> URadarComponent::GetDetectedAllies() const
{
	return DetectedAllies;
}

TArray<AActor*> URadarComponent::GetDetectedEnemies() const
{
	return DetectedEnemies;
}

AActor * URadarComponent::GetClosestEnemyActor(ETargetTypeEnum TargetType)
{
	if (DetectedEnemies.Num() > 0)
	{
		TArray<AActor*> ActorsOfType;

		for (int32 i = 0; i < DetectedEnemies.Num(); i++) {
			if (DetectedEnemies[i]->FindComponentByClass<URadarRegistrarComponent>()->GetTargetType() == TargetType) {
				ActorsOfType.Add(DetectedEnemies[i]);
			}
		}

		if (ActorsOfType.Num() > 0) {
			int32 ClosestIndex = 0;

			FVector RadarLoc = GetOwner()->GetActorLocation();
			FVector PawnLoc = ActorsOfType[0]->GetActorLocation();

			FVector OutDir;
			float OutLen;

			(RadarLoc - PawnLoc).ToDirectionAndLength(OutDir, OutLen);
			float ClosestDst = OutLen;

			for (int32 i = 1; i < ActorsOfType.Num(); i++)
			{
				if (ActorsOfType[i]->FindComponentByClass<URadarRegistrarComponent>()->GetTargetType() == TargetType) {
					PawnLoc = ActorsOfType[i]->GetActorLocation();
					(RadarLoc - PawnLoc).ToDirectionAndLength(OutDir, OutLen);
					if (OutLen < ClosestDst)
					{
						ClosestDst = OutLen;
						ClosestIndex = i;
					}
				}
			}

			return ActorsOfType[ClosestIndex];
		}
	}

	return nullptr;
}

void URadarComponent::SetIgnorePlayer(bool IgnorePlayer)
{
	bIgnorePlayer = IgnorePlayer;
}

void URadarComponent::RadarBurst()
{
	if (!bRadarEnabled) return;

	EFactionEnum MyFaction;

	// TODO Store EFactionEnum in a better, consistant place
	// Something like, Cast<APawn>(GetOwner())->GetComponent(FactionComponent)->GetFaction()
	URadarRegistrarComponent * RadarRegistrarComponent = GetOwner()->FindComponentByClass<URadarRegistrarComponent>();
	if (RadarRegistrarComponent) {
		MyFaction = RadarRegistrarComponent->GetFaction();
	}
	else {
		// TODO Set Faction on weapon when picked up. This would however only be useful
		// if there is an extension of this game to multiplayer, or humanoid based AI
		// Assume Weapon is player weapon
		MyFaction = EFactionEnum::FE_Good;
	}

	// Clear relevant arrays
	DetectedAllies.Empty();
	DetectedEnemies.Empty();

	// Get Singleton List (GameMode)
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());

	TArray<AActor *> DetectedAllieActors = GameMode->GetAlliedRadarDetectableActors(MyFaction);

	TArray<AActor *> DetectedEnemieActors = GameMode->GetOpposingRadarDetectableActors(MyFaction);

	

	// Get Allies within range
	for(int32 i = 0; i < DetectedAllieActors.Num(); i++)
	{
		FString PawnName = DetectedAllieActors[i]->GetName();

		// If this pawn is not the owner pawn
		if(DetectedAllieActors[i] != Cast<AActor>(GetOwner()))
		{
			// Check if Actor is within range, if so raycast to pawn to check if it is in view
			if (IsActorWithinRange(DetectedAllieActors[i]) && IsActorRadarVisible(DetectedAllieActors[i]))
			{
				DetectedAllies.Add(DetectedAllieActors[i]);
			}
		}
	}

	// Get Enemies within range
	for (int32 i = 0; i < DetectedEnemieActors.Num(); i++)
	{
		FString PawnName = DetectedEnemieActors[i]->GetName();

		// If this pawn is not the owner pawn
		if (DetectedEnemieActors[i] != Cast<AActor>(GetOwner()))
		{
			// Check if Actor is within range, if so raycast to pawn to check if it is in view
			if (IsActorWithinRange(DetectedEnemieActors[i]) && IsActorRadarVisible(DetectedEnemieActors[i]))
			{
				DetectedEnemies.Add(DetectedEnemieActors[i]);
			}
		}
	}

	
	FTimerHandle RadarBurstTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		RadarBurstTimerHandle,
		this,
		&URadarComponent::RadarBurst,
		RadarBurstRate,
		false
	);
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
