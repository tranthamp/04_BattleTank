// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile() {
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

void AProjectile::LaunchProjectile(float LaunchSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("Projectile fires at %f!"), LaunchSpeed);
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector* LaunchSpeed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::BeginPlay() {
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}