// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "gameplaytags.h"


#include "AuraPlayerController.generated.h"


class UDamageTextComponent;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;
/**
 * 
 */
UCLASS()
class UEGAS_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void PlayerTick(float DeltaTime) override;
	AAuraPlayerController();

	UFUNCTION(Client,Reliable)
	void ShowDamageNumber(float DamageAmount,AActor* TargetCharacter);
protected:
	virtual void BeginPlay() override;
	virtual  void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ShiftAction;
	
	void Move(const FInputActionValue& InputActionValue);

	void ShiftPressed() {bShiftKeyDown = true;}
	void ShiftReleased() {bShiftKeyDown = false;}
	bool bShiftKeyDown = false;
	
	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag ReleasedTag);
	void AbilityInputTagHeld(FGameplayTag HeldTag);
	
	UPROPERTY(EditDefaultsOnly,category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
