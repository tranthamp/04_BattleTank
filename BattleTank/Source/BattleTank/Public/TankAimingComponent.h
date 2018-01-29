// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	RELOADING,
	AIMING,
	LOCKED
};

class UTankBarrel;
class UTankTurret;

// Holds data and methods for aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void AimAt(FVector HitLocation, float LaunchSpeed);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::LOCKED;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
};
