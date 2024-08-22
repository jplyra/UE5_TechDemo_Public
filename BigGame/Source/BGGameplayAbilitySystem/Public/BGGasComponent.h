// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BGGasComponent.generated.h"

UCLASS()
class BGGAMEPLAYABILITYSYSTEM_API UBGGasComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;
	
};
