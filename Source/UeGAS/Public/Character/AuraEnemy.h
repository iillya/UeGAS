// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
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
protected:
	virtual void BeginPlay() override;
};
