// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.H"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include  "UeGAS/Public/AuraGameplayTags.h"



void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation,const FGameplayTag& SocketTag,bool bOverridePitch,float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetAvatarActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	TArray<TWeakObjectPtr<AActor>> Actors;
	EffectContextHandle.AddActors(Actors);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);

	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),EffectContextHandle);
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	
	for (auto DamageTypeTag : DamageTypeTags)
	{
		if (DamageTypes.Find(DamageTypeTag) != nullptr)
		{
			const float ScaledDamage = DamageTypes.Find(DamageTypeTag)->GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DamageTypeTag,ScaledDamage);
		}
		else
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DamageTypeTag,0.f);
		}
	}
	
	Projectile->DamageEffectSpecHandle = SpecHandle;
	
	Projectile->FinishSpawning(SpawnTransform);

}
	