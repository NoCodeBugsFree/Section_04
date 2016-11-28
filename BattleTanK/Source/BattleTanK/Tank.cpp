// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	// can fire at start game
	LastFireTime = GetWorld()->TimeSeconds - ReloadTimeInSeconds;

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

	if (!ensure(TankAimingComponent)) { return; }
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATank::Fire()
{	
	// FPlatformTime::Seconds()
	bool bIsReloaded = GetWorld()->TimeSeconds - LastFireTime > ReloadTimeInSeconds;
	if (bIsReloaded)
	{
		auto World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			if (!ensure(TankAimingComponent)) { return; }

			FTransform SpawnTransform = TankAimingComponent->GetBarrelSocketTransform();
			AProjectile* SpawnedProjectile = World->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnTransform, SpawnParams);

			if (!ensure(SpawnedProjectile)) { return; }
			
			SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		}

		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
