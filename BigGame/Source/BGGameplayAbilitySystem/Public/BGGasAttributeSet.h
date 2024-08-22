// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BGGasAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class BGGAMEPLAYABILITYSYSTEM_API UBGGasAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBGGasAttributeSet();
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	DECLARE_DELEGATE_OneParam(FBGOnGasAttributeChange, float);

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, MoveSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttack", ReplicatedUsing = OnRep_BaseAttack)
	FGameplayAttributeData BaseAttack;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, BaseAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Ki", ReplicatedUsing = OnRep_Ki)
	FGameplayAttributeData Ki;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, Ki)

	UPROPERTY(BlueprintReadOnly, Category = "Ki", ReplicatedUsing = OnRep_MaxKi)
	FGameplayAttributeData MaxKi;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, MaxKi)

	UPROPERTY(BlueprintReadOnly, Category = "Poise", ReplicatedUsing = OnRep_Poise)
	FGameplayAttributeData Poise;
	ATTRIBUTE_ACCESSORS(UBGGasAttributeSet, Poise)

	FBGOnGasAttributeChange OnMoveSpeedChange{};

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_BaseAttack(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Ki(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxKi(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Poise(const FGameplayAttributeData& OldValue);
};
