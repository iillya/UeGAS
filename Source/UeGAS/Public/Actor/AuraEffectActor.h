// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;
class UGameplayEffect;
class UAbilitySystemComponent;
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};


UCLASS()
class UEGAS_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraEffectActor();



protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlay(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlay(AActor* TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;


	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;
private:


};
