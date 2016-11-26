// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Error, TEXT("%s throttle : %f"), *Name, Throttle);

	// TODO clamp Throttle so player can't overdrive
}
