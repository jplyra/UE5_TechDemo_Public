// Fill out your copyright notice in the Description page of Project Settings.


#include "BGGasAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UBGGasAttributeSet::UBGGasAttributeSet()
{
	
}

void UBGGasAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(), 0.0f, 100.0f));
	}

	if (Data.EvaluatedData.Attribute == GetKiAttribute())
	{
		SetKi(FMath::Clamp(GetKi(), 0.0f, GetMaxKi()));
	}

	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		std::ignore = OnMoveSpeedChange.ExecuteIfBound(GetMoveSpeed());
	}
}

void UBGGasAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, BaseAttack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, Ki, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, MaxKi, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBGGasAttributeSet, Poise, COND_None, REPNOTIFY_Always);
}

void UBGGasAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, Health, OldValue);
}

void UBGGasAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, MaxHealth, OldValue);
}

void UBGGasAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, Armor, OldValue);
}

void UBGGasAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, MoveSpeed, OldValue);
}

void UBGGasAttributeSet::OnRep_BaseAttack(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, BaseAttack, OldValue);
}

void UBGGasAttributeSet::OnRep_Ki(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, Ki, OldValue);
}

void UBGGasAttributeSet::OnRep_MaxKi(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, MaxKi, OldValue);
}

void UBGGasAttributeSet::OnRep_Poise(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBGGasAttributeSet, Poise, OldValue);
}
