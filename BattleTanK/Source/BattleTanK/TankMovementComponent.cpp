// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
		// TODO prevent double speed due to dual control use
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
		// TODO prevent double speed due to dual control use
	}
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (LeftTrackToSet && RightTrackToSet)
	{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	} 
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UTankMovementComponent::Initialize ERRROR "));
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No super - we're replacing - in general way path finding logic call Super to move AI
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Calculate the dot product of two vectors.
	// A * B = ||A|| ||B|| cos @, where is @ is angle between A and B
	// Y-axis is throw and X-axis is AIForwardIntention
	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);

	IntendMoveForward(ForwardThrow);
}
