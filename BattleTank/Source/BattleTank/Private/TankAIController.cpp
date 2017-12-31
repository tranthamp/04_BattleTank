// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	AiTank = GetControlledTank();
	if (AiTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(AiTank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT possessing a Tank"));
	}

	PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController PlayerTank: %s"), *(PlayerTank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NO PlayerTank"));
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (AiTank && PlayerTank) {
		AiTank->AimAt(PlayerTank->GetActorLocation());
	}
}