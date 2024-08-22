// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BGGasAttributeSet.h"
#include "BGGasComponent.h"
#include "GameFramework/PlayerState.h"
#include "BGPlayerState.generated.h"

UCLASS()
class BIGGAME_API ABGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UBGGasComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UBGGasAttributeSet> AttributeSet;

	ABGPlayerState();

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent; }

	FORCEINLINE UBGGasAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
