// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack - move by applying forces ...
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	/** Sets a throttle between - 1 and + 1   */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetThrottle(float Throttle);

	UTankTrack();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;

protected:



private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/** Max force per track in Newtons */
	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float TrackMaxDrivingForce = 40000000; // assume 40 tonne tank and 1g acceleration
};
