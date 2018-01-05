// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Values from -1 to 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

private:
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDrivingForce = 400000.0f; // 40000 kg * 10 m/(s*s)
};
