// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay"));

	ATank* Tank = GetControlledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT possessing a Tank"));
	}
}