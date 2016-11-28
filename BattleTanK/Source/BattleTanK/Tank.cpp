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

			if (TankAimingComponent == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("TankAimingComponent == nullptr"));
				return;
			}
			FTransform SpawnTransform = TankAimingComponent->GetBarrelSocketTransform();
			AProjectile* SpawnedProjectile = World->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnTransform, SpawnParams);

			if (SpawnedProjectile)
			{
				SpawnedProjectile->LaunchProjectile(LaunchSpeed);
			}
		}

		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
