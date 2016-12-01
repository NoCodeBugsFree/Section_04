// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM(BlueprintType)
enum class EFiringState : uint8 // uint8 - cross platform independence
{
	Locked, 
	Aiming,
	Reloading,
	OutOfAmmo
};


class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	/** Tank Fires  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Fire();
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "AAA")
	EFiringState GetFiringState() const { return FiringState; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetRoundsLeft() const { return RoundsLeft; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EFiringState FiringState = EFiringState::Reloading;

private:

	FVector AimDirection;

	bool IsBarrelMoving();

	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowards();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UTankBarrel* Barrel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UTankTurret* Turret;

	/**  sensible starting value 1700 m/s */
	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float ReloadTimeInSeconds = 3.f;

	float LastFireTime = -ReloadTimeInSeconds; // to be able fire instantly after level start

	UPROPERTY(meta = (ClampMin = "0"), EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 RoundsLeft = 10;

};
