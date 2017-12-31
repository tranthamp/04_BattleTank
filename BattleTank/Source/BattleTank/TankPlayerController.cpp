// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(Tank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController NOT possessing a Tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	ATank* OurTank = GetControlledTank();
	if (!OurTank) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		OurTank->AimAt(HitLocation);
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// Deproject the screen position to the world position
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction (up to some maximum range)
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const {
   	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
   	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility)) {
   		OutHitLocation = HitResult.Location;
   		return true;
   	}
	OutHitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const {
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, OutLookDirection);
}