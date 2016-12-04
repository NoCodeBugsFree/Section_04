// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h" 
#include "TankAimingComponent.h" // TODO REMOVE

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
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		// DIE
	}
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth / StartingHealth;
}

float ATank::GetCurrentHealth() const
{
	return CurrentHealth;
}

