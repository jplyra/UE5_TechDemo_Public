// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGGameplayAbilitySystem/Public/BGGasAttributeSet.h"
#include "BGWidgetController.h"
#include "BGOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class BGWIDGETSYSTEM_API UBGOverlayWidgetController : public UBGWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged{};

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged{};
	
	virtual void BroadcastInitialValues() override;
	
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnKiChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxKiChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	
	void KiChanged(const FOnAttributeChangeData& Data) const;

	void MaxKiChanged(const FOnAttributeChangeData& Data) const;
};
