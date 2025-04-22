// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class UEGAS_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;
	
	
	/** EnemyInterface */
	virtual  void HighlightActor();
	virtual  void UnHighlightActor();
	/** End EnemyInterface */
	
	/** CombatInterface */
	virtual void Die() override;
	virtual int32 GetPlayerLevel() override;
	virtual  void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual  AActor* GetCombatTarget_Implementation() const override;
	/**End CombatInterface */
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSinature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSinature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag,int32 NewCount);

	UPROPERTY(BlueprintReadOnly,category = "Combat")
	bool bHitReacting;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite,category = "Combat")
	TObjectPtr<AActor> CombatTarget;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere,Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;

};
