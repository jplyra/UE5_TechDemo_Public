// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGDamageable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BGCombatFunctionLibrary.generated.h"

UCLASS()
class BGCOMBATSYSTEM_API UBGCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool TryApplyDamage(AActor* Instigator, AActor* CombatTarget, FBGDamage Damage);
};
