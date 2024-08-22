// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/BGOverlayWidgetController.h"
#include "BGGameplayAbilitySystem/Public/BGGasAttributeSet.h"

void UBGOverlayWidgetController::BroadcastInitialValues()
{
	const UBGGasAttributeSet* BGGasAttributeSet = CastChecked<UBGGasAttributeSet>(WidgetParams.AttributeSet);

	OnHealthChanged.Broadcast(BGGasAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BGGasAttributeSet->GetMaxHealth());
	OnKiChanged.Broadcast(BGGasAttributeSet->GetKi());
	OnMaxKiChanged.Broadcast(BGGasAttributeSet->GetMaxKi());
}

void UBGOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBGGasAttributeSet* BGGasAttributeSet = CastChecked<UBGGasAttributeSet>(WidgetParams.AttributeSet);

	WidgetParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BGGasAttributeSet->GetHealthAttribute()).AddUObject(this, &UBGOverlayWidgetController::HealthChanged);

	WidgetParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BGGasAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UBGOverlayWidgetController::MaxHealthChanged);

	WidgetParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BGGasAttributeSet->GetKiAttribute()).AddUObject(this, &UBGOverlayWidgetController::KiChanged);

	WidgetParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BGGasAttributeSet->GetMaxKiAttribute()).AddUObject(this, &UBGOverlayWidgetController::MaxKiChanged);
}

void UBGOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UBGOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UBGOverlayWidgetController::KiChanged(const FOnAttributeChangeData& Data) const
{
	OnKiChanged.Broadcast(Data.NewValue);
}

void UBGOverlayWidgetController::MaxKiChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxKiChanged.Broadcast(Data.NewValue);
}