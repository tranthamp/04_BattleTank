// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	AiTank = Cast<ATank>(GetPawn());
	if (!AiTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController: NOT possessing a Tank"));
	}
	
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController: NO PlayerTank"));
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (AiTank && PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);
		AiTank->AimAt(PlayerTank->GetActorLocation());
		AiTank->Fire();
	}
}