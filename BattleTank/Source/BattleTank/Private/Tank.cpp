// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

float ATank::GetHealthPercent() const {
	return (float)CurrentHealth / (float)StartingHealth;
}

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth == 0) {
		OnDeath.Broadcast();
	}
	return DamageToApply;
}
