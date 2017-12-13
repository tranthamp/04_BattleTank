// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* AiTank = GetControlledTank();
	if (AiTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(AiTank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT possessing a Tank"));
	}

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController PlayerTank: %s"), *(PlayerTank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NO PlayerTank"));
	}
}
