// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

	/** Tank Fires  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Fire();
	
protected:


private:

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	/**  sensible starting value 1700 m/s */
	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float ReloadTimeInSeconds = 3.f;

	float LastFireTime = 0.f;

	UPROPERTY()
	UTankAimingComponent* TankAimingComponent;

};
