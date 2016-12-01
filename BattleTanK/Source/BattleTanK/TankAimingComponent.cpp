// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h" 

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->TimeSeconds; // Ben wants initial reload ??? =)
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	if (Ammo <= 0)
	{
		FiringState = EFiringState::Locked;
	}
	else if (GetWorld()->TimeSeconds - LastFireTime < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
	}
	else 
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Fire()
{	
	if (FiringState != EFiringState::Reloading && Ammo > 0)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto World = GetWorld();
		if (World)
		{
			FTransform SpawnTransform = Barrel->GetSocketTransform("Projectile");
		
			AProjectile* SpawnedProjectile = World->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnTransform);

			if (!ensure(SpawnedProjectile)) { return; }

			Ammo--;

			SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		}
		
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, 
		HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace));

	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	} // no aiming solution found ...
}

void UTankAimingComponent::Initialize(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet)
{
	if (!ensure(TankBarrelToSet && TankTurretToSet)) { return; }
	
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel && Turret)) { return; }

	// Work-out difference between current barrel rotation and AimDirection

	// Return the FRotator orientation corresponding to the direction in which the vector points.
	// Sets Yaw and Pitch to the proper numbers, and sets Roll to zero because the roll can't be determined from a vector
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	
	// Move the barrel and turret the right amount this frame
	// Always Yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch); 
	if (DeltaRotator.Yaw < 180.f)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	} 
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector BarrelForwardFector = Barrel->GetForwardVector();

	// bool FVector::Equals(const FVector& V, float Tolerance)
	// true if the vectors are equal within tolerance limits, false otherwise
	return !BarrelForwardFector.Equals(AimDirection, 0.01f);
}
