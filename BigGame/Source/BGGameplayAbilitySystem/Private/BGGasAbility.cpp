// Fill out your copyright notice in the Description page of Project Settings.


#include "BGGasAbility.h"

#include "AbilitySystemComponent.h"
#include "BGGasCharacter.h"
#include "GameFramework/GameStateBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogBGGasAbility, Log, All)

UBGGasAbility::UBGGasAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UBGGasAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityWhenGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

float UBGGasAbility::GetCooldownRemaining() const
{
	return FMath::Max(CooldownExpirationTime - GetServerTime(), 0.0f);
}

float UBGGasAbility::IsAbilityInCooldown() const
{
	return GetCooldownRemaining() > 0.0f;
}

ABGGasCharacter* UBGGasAbility::GetGasCharacter() const
{
	ABGGasCharacter* GasCharacter = Cast<ABGGasCharacter>(GetAvatarActorFromActorInfo());
	return GasCharacter;
}

void UBGGasAbility::ApplyGameplayEffectByMagnitude(const TSubclassOf<UBGGasEffect> EffectClass, float Magnitude, FGameplayTag MagnitudeTag)
{
	UAbilitySystemComponent* GasComponent = GetAbilitySystemComponentFromActorInfo();

	if (!GasComponent)
	{
		UE_LOG(LogBGGasAbility, Warning, TEXT("GasComponent is invalid."));
		return;
	}
	
	FGameplayEffectContextHandle EffectContextHandle = GasComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =  GasComponent->MakeOutgoingSpec(EffectClass, 1.0f, EffectContextHandle);
	
	if (EffectSpecHandle.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(MagnitudeTag, Magnitude);
		GasComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UBGGasAbility::CommitExecute(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::CommitExecute(Handle, ActorInfo, ActivationInfo);

	ApplyCustomCooldown();
}

bool UBGGasAbility::CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	return !IsAbilityInCooldown();
}

void UBGGasAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	EnsureCooldownConditions();
}

float UBGGasAbility::GetCooldownTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return GetCooldownRemaining();
}

void UBGGasAbility::GetCooldownTimeRemainingAndDuration(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, float& TimeRemaining, float& CooldownDuration) const
{
	TimeRemaining = GetCooldownRemaining();
	CooldownDuration = AbilityCooldownBase;
}

float UBGGasAbility::GetServerTime() const
{
	if (const UWorld* World = GetWorld())
	{
		if (const AGameStateBase* GameState = World->GetGameState())
		{
			return GameState->GetServerWorldTimeSeconds();
		}
	}

	return 0.0f;
}

void UBGGasAbility::EnsureCooldownConditions() const
{
	ensure(InstancingPolicy == EGameplayAbilityInstancingPolicy::InstancedPerActor);
	ensure(NetExecutionPolicy != EGameplayAbilityNetExecutionPolicy::ServerInitiated);
}

void UBGGasAbility::ApplyCustomCooldown()
{
	CooldownExpirationTime = GetServerTime() + AbilityCooldownBase;
}