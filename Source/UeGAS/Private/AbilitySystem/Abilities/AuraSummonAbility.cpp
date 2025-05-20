// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraSummonAbility.h"


void UAuraSummonAbility::GetSpawnLocations(TArray<FVector>& SpawnLocations)
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;
	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2,FVector::UpVector);
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread*i,FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance,MaxSpawnDistance);
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit,ChosenSpawnLocation + FVector(0,0,400),ChosenSpawnLocation - FVector(0,0,400),ECC_Visibility);
		if (Hit.IsValidBlockingHit())
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	
}
