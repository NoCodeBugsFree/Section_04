// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM(BlueprintType)
enum class EFiringState : uint8 // uint8 - cross platform independence
{
	Locked, 
	Aiming,
	Reloading
};


class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	void AimAt(FVector HitLocation, float LaunchSpeed);

	FTransform GetBarrelSocketTransform() const;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:



private:

	void MoveBarrelTowards(FVector AimDirection);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UTankBarrel* Barrel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UTankTurret* Turret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EFiringState FiringStatus = EFiringState::Locked;
	
};
