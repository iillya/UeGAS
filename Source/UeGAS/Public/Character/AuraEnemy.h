// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class UEGAS_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
	
	/** EnemyInterface */
	virtual  void HighlightActor();
	virtual  void UnHighlightActor();
	/** End EnemyInterface */
	
	/** CombatInterface */
	virtual int32 GetPlayerLevel() override;
	/**End CombatInterface */
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSinature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSinature OnMaxHealthChanged;
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
};
