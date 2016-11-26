// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp Throttle so player can't overdrive
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());;
	if (TankRoot)
	{
		// Add a force to a single rigid body at a particular location. 
		// This is like a 'thruster'. Good for adding a burst over some (non zero) time. 
		// Should be called every frame for the duration of the force.
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}
