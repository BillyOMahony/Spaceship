// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondaryThruster.h"

void USecondaryThruster::BeginPlay() {
	Super::BeginPlay();

}

void USecondaryThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
}

void USecondaryThruster::AddForceInDirection()
{

}

void USecondaryThruster::SetThrottle(float Throttle)
{
	this->Throttle = Throttle;
}
