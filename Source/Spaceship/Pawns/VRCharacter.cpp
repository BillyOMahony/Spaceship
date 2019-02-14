// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "TimerManager.h"
#include "SpaceshipGameModeBase.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("VR Root")));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	Camera->SetupAttachment(VRRoot);
	Camera->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Register Pawn with GameMode RadarDetectablePawns
	auto GameMode = Cast<ASpaceshipGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->RegisterWithRadarDetectablePawns(this, Faction);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASpaceshipPawn::BeginPlay - Cannot find GameMode"));
	}
	// TODO Set Faction in GameMode
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCameraComponent * AVRCharacter::GetCamera()
{
	return Camera;
}

void AVRCharacter::DirectTeleport(FTransform TeleportTransform)
{
	FRotator RootRotator = Camera->GetComponentRotation();

	FRotator ArrowRotator = TeleportTransform.GetRotation().Rotator();

	SetActorLocation(TeleportTransform.GetLocation());

	// Set Rotation
	FRotator Difference = ArrowRotator - RootRotator;
	VRRoot->AddLocalRotation(FRotator(0, Difference.Yaw, 0));


	// Recenter
	FVector Offset = Camera->GetComponentLocation() - TeleportTransform.GetLocation();
	Offset.Z = 0;

	VRRoot->AddWorldOffset(-Offset);
}

void AVRCharacter::MoveForward(float scale)
{
	// Get the direction the camera is facing. The character is moved in this direction. 
	FVector ForwardVector = Camera->GetForwardVector();
	
	AddMovementInput(ForwardVector.GetSafeNormal(), scale * SpeedMultiplier);
}

void AVRCharacter::MoveRight(float scale)
{
	// Get the direction to the right of the direction the camera is facing. The character is moved in this direction. 
	FVector RightVector = Camera->GetRightVector();

	AddMovementInput(RightVector.GetSafeNormal(), scale * SpeedMultiplier);
}

void AVRCharacter::RotateCamera(float Direction)
{
	FVector CamStartLoc = Camera->GetComponentLocation();

	FRotator RotationToAdd = FRotator(0, 45 * Direction, 0);
	VRRoot->AddLocalRotation(RotationToAdd);

	FVector Offset = Camera->GetComponentLocation() - CamStartLoc;
	Offset.Z = 0;

	VRRoot->AddWorldOffset(-Offset);
}

void AVRCharacter::FadeToColor(float Duration, bool bHoldWhenFinished, FLinearColor Color)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->PlayerCameraManager->StartCameraFade(0, 1, Duration, Color, false, bHoldWhenFinished);
	}
}

void AVRCharacter::TeleportCharacter(FTransform TeleportTransform)
{
	FadeToColor(FadeDuration, true, FLinearColor::White);
	
	// Teleport
	FTimerHandle Handle;
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AVRCharacter::TeleportToLocation, TeleportTransform, FLinearColor::White);

	GetWorldTimerManager().SetTimer(Handle, Delegate, FadeDuration + 1.f, false);
}


void AVRCharacter::TeleportToLocation(FTransform Location, FLinearColor Color)
{
	FRotator RootRotator = Camera->GetComponentRotation();

	FRotator ArrowRotator = Location.GetRotation().Rotator();

	SetActorLocation(Location.GetLocation());

	// Set Rotation
	FRotator Difference = ArrowRotator - RootRotator;
	VRRoot->AddLocalRotation(FRotator(0, Difference.Yaw, 0));

	
	// Recenter
	FVector Offset = Camera->GetComponentLocation() - Location.GetLocation();
	Offset.Z = 0;

	VRRoot->AddWorldOffset(-Offset);

	// Fade Back in
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->PlayerCameraManager->StartCameraFade(1, 0, FadeDuration, Color);
	}


}

