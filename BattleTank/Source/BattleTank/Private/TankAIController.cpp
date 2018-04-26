// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank)) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius);

	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::LOCKED) {
		AimingComponent->Fire();
	}
}

void ATankAIController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("TankAIController - Tank is dead, detaching pawn from controller"));
	GetPawn()->DetachFromControllerPendingDestroy();
}