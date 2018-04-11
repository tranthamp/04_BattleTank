// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile() {
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

void AProjectile::LaunchProjectile(float LaunchSpeed) {
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector* LaunchSpeed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::BeginPlay() {
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}