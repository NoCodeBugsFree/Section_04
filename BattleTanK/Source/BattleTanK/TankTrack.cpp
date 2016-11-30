// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// calculate the slippage speed - tank right direction
	// if no slippage should be zero, if sliding entirely sideways, should be speed
	// use cos of the angle between velocity and right vector

	// FVector UPrimitiveComponent::GetComponentVelocity() - Get velocity of the component:
	// either ComponentVelocity, or the velocity of the physics body if simulating physics. 

	// FVector USceneComponent::GetRightVector()
	// Get the right (Y) unit direction vector from this component, in world space

	float SleppageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	
	// work-out the required acceleration this frame to correct
	FVector CorrectionAcceleration = - SleppageSpeed / DeltaTime * GetRightVector();

	// calculate and apply sideways for F = m * a
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
	
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT("UTankTrack::OnHit"));
}

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp Throttle so player can't overdrive
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }
	
	// Add a force to a single rigid body at a particular location. 
	// This is like a 'thruster'. Good for adding a burst over some (non zero) time. 
	// Should be called every frame for the duration of the force.
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


