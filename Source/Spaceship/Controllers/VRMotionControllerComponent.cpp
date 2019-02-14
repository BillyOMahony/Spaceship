// Fill out your copyright notice in the Description page of Project Settings.

#include "VRMotionControllerComponent.h"

UVRMotionControllerComponent::UVRMotionControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	HandMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("HandMesh"));
	HandMesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	HandMesh->SetupAttachment(this);
}

void UVRMotionControllerComponent::BeginPlay()
{
	Super::BeginPlay();
}