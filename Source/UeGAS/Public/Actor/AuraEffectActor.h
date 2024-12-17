// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;
class UGameplayEffect;

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
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	
private:


};
