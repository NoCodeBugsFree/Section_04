// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No super - we're replacing - in general way path finding logic call Super to move AI
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Calculate the dot product of two vectors.
	// A DOT B = ||A|| ||B|| cos @  , where @ is angle between A and B  // DOT IS POINT .  
	// Y-axis is throw and X-axis is AIForwardIntention
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	// Calculate the cross product of two vectors.
	// A CROSS  B = ||A|| ||B|| sin @  N , where @ is angle between A and B in the plain  // * is Cross
	// containing them (hence, it is between 0 and 180), ||A|| and ||B|| are the magnitudes
	// and N is a unit vector perpendicular to the plane
	FVector RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendTurnRight(RightThrow.Z); // Z - remember wiki diagram
}
