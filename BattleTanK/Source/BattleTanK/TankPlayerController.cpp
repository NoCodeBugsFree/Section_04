// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(TankAimingComponent)) { return; }
	
	FoundAimingComponent(TankAimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }
	
	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // has a "side-effect". is going to linetrace 
	{
		TankAimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;

	// Helper to get the size of the HUD canvas for this player controller. 
	// Returns 0 if there is no HUD
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// aim dot location on screen
	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);
	
	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// linetrace along that look direction and see what we hit (up to max range)
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			// TODO WTF here?
		}
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// APlayerController::DeprojectScreenPositionToWorld
	// Convert current mouse 2D position to World Space 3D position and direction. 
	// Returns false if unable to determine value.

	FVector CameraWorldLocation; // to be ignored
	// ignore CameraWorldLocation - it's camera world location
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation(); // may be muzzle location ?
	FVector EndLocation = StartLocation + LineTraceRange * LookDirection;
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}

