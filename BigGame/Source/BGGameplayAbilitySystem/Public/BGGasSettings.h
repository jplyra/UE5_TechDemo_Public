// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGGasEffect.h"
#include "GameplayTagContainer.h"
#include "BGUserSettings.h"
#include "BGGasSettings.generated.h"

UCLASS()
class BGGAMEPLAYABILITYSYSTEM_API UBGGasSettings : public UBGUserSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category= "Damage")
	TSubclassOf<UBGGasEffect> DamageEffectClass{};
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category= "Damage")
	FGameplayTag DamageTag{};

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category= "Damage")
	FGameplayTag OnHitEventTag{};
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category= "Dead")
	FGameplayTag OnDeadEventTag{};

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category= "Falling")
	FGameplayTag IsFallingTag{};

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category= "Falling")
	FGameplayTag IsGroundedTag{};
};
