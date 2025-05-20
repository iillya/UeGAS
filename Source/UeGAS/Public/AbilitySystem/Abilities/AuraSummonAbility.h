// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class UEGAS_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void GetSpawnLocations(TArray<FVector>& SpawnLocations);

	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	int32 NumMinions = 5;
	
	UPROPERTY(EDITDefaultsOnly,Category="Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EDITDefaultsOnly,Category="Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EDITDefaultsOnly,Category="Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EDITDefaultsOnly,Category="Summoning")
	float SpawnSpread = 90.f;
};
