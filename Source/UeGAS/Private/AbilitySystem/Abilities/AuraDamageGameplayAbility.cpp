// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.H"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass,1);
	TArray<FGameplayTag> DamageTypeKeys;
	DamageTypes.GenerateKeyArray(DamageTypeKeys);
	TArray<FScalableFloat> DamageTypeValues;
	DamageTypes.GenerateValueArray(DamageTypeValues);
	for (const auto& DamageTypeTag : DamageTypeTags)
	{
		int32 Index = DamageTypeKeys.Find(DamageTypeTag);
		if ( Index > -1)
		{
			const float ScaledDamage = DamageTypeValues[Index].GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle,DamageTypeTag,ScaledDamage);
			
		}
		else
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle,DamageTypeTag,0.f);
		}
		
	}
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

UAuraDamageGameplayAbility::UAuraDamageGameplayAbility()
{
	DamageTypeTags.AddUnique(FAuraGameplayTags::Get().Damage_Arcane);
	DamageTypeTags.AddUnique(FAuraGameplayTags::Get().Damage_Fire);
	DamageTypeTags.AddUnique(FAuraGameplayTags::Get().Damage_Lightning);
	DamageTypeTags.AddUnique(FAuraGameplayTags::Get().Damage_Physical);
	DamageTypeTags.AddUnique(FAuraGameplayTags::Get().Damage);
}


FTaggedMontage UAuraDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages)
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0,TaggedMontages.Num()-1);
		return TaggedMontages[Selection];
	}
	return FTaggedMontage();
}
