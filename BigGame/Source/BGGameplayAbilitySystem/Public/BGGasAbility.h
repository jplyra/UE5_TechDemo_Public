// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGGasEffect.h"
#include "Abilities/GameplayAbility.h"
#include "BGGasAbility.generated.h"

class ABGGasCharacter;

UCLASS()
class BGGAMEPLAYABILITYSYSTEM_API UBGGasAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Config")
	bool bActivateAbilityWhenGranted = false;

	UPROPERTY(EditAnywhere, Category = "Config", meta=(ClampMin = 0))
	float AbilityCooldownBase{};

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter = "GetAbilityCooldownExpirationTime")
	float CooldownExpirationTime{};
	
public:
	UBGGasAbility();

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	UFUNCTION(BlueprintGetter)
	FORCEINLINE float GetAbilityCooldownExpirationTime() const { return CooldownExpirationTime; }

	UFUNCTION(BlueprintPure)
	float GetCooldownRemaining() const;

	UFUNCTION(BlueprintPure)
	float IsAbilityInCooldown() const;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ResetCooldown() { CooldownExpirationTime = 0; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCooldownReduction(float TimeInSeconds) { CooldownExpirationTime -= TimeInSeconds; }

	UFUNCTION(BlueprintPure)
	ABGGasCharacter* GetGasCharacter() const;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectByMagnitude(const TSubclassOf<UBGGasEffect> EffectClass, float Magnitude, FGameplayTag MagnitudeTag);
protected:
	virtual void CommitExecute(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual float GetCooldownTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const override;

	virtual void GetCooldownTimeRemainingAndDuration(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, float& TimeRemaining, float& CooldownDuration) const override;

	float GetServerTime() const;

	void EnsureCooldownConditions() const;

	UFUNCTION(BlueprintCallable)
	void ApplyCustomCooldown();
	
};
