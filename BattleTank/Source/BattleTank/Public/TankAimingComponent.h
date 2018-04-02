// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	RELOADING,
	AIMING,
	LOCKED,
	OUT_OF_AMMO
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds data and methods for aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::RELOADING;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3.0f;

	int RoundsLeft = 3;

	double LastFireTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	FVector AimDirection;

	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool IsBarrelMoving() const;
};
