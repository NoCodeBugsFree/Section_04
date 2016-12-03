// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanK.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionMesh"));
	SetRootComponent(CollisionMesh);

	// this one set the generate hit events in BP editor to true
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LaunchBlast"));
	LaunchBlast->SetupAttachment(RootComponent);
	LaunchBlast->bAutoActivate = true;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ImpactBlast"));
	// FAttachmentTransformRules - Rules for attaching components
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosionForce"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		LaunchBlast->Deactivate();
		ImpactBlast->Activate();
		ExplosionForce->FireImpulse();
		
		SetRootComponent(ImpactBlast);
		CollisionMesh->DestroyComponent();

		FTimerHandle DestroyTimer;
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
	}
}

