// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


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

}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, 
		HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace));

	if(bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	} // no aiming solution found ...
}

FTransform UTankAimingComponent::GetBarrelSocketTransform() const
{
	if (!ensure(Barrel))
	{
		return FTransform();
	}
	
	return Barrel->GetSocketTransform("Projectile");
}

void UTankAimingComponent::Initialize(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet)
{
	if (!ensure(TankBarrelToSet && TankTurretToSet)) { return; }
	
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and AimDirection

	// Return the FRotator orientation corresponding to the direction in which the vector points.
	// Sets Yaw and Pitch to the proper numbers, and sets Roll to zero because the roll can't be determined from a vector
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	
	// Move the barrel and turret the right amount this frame
	if (!ensure(Barrel && Turret)) { return; }

	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
}

